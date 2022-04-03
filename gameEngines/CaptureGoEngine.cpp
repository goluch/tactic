#include "CaptureGoEngine.h"
#include <assert.h>

using namespace gameEngines;

unsigned int CaptureGoEngine::boardSize;
unsigned int CaptureGoEngine::fieldsNumber;
unsigned int GameEngine::maxPossibleMoves;

unsigned long long CaptureGoEngine::endOfBoardMask;
// maska p�l osi�galnych po ruchu o jedno pole w lewo
// innymi s�owy - posiadaj�cych po prawej wolne pole (nie granicz�cymi po prawej z plansz�)
unsigned long long CaptureGoEngine::leftBorderMask;
// maska p�l dozwolonych po ruchu o jedno pole w prawo
// innymi s�owy - posiadaj�cych po lewej wolne pole (nie granicz�cymi po lewej z plansz�)
unsigned long long CaptureGoEngine::rightBorderMask;
// maska wszystkich p�l
unsigned long long CaptureGoEngine::fullBoardMask;
// pomocnicze pola wykorzystywane podczas sprawdzania zako�czenia rozgrywki
unsigned long long CaptureGoEngine::possiblyDeadBlackPawns;
unsigned long long CaptureGoEngine::possiblyDeadWhitePawns;

void CaptureGoEngine::initialize()
{
	GameEngine::maxPossibleMoves = fieldsNumber = boardSize * boardSize;
	fullBoardMask = 1;
	for (int i = 1; i < fieldsNumber; i++)
	{
		fullBoardMask <<= 1;
		fullBoardMask += 1;
	}
	endOfBoardMask = 1 << fieldsNumber;
	if (fieldsNumber == 64) endOfBoardMask = 0;
	leftBorderMask = rightBorderMask = 0;
	unsigned long long i = 1;
	int j = 0;
	for (unsigned long long i = 1; i != endOfBoardMask; i <<= 1, j++)
	{
		if ((j + 1) % boardSize) leftBorderMask |= i;
		if (j % boardSize) rightBorderMask |= i;
	}
	endOfBoardMask--;
}

unsigned long long CaptureGoEngine::pawnsFromStringToLong(char *pawnsString)
{
	unsigned long long pawnsNumber = 0;
	int j = -1;
	for (unsigned long long i = 1; i != 0; i <<= 1)
	{
		j++;
		if (pawnsString[j] == '0') continue;
		else if (pawnsString[j] == '1') pawnsNumber |= i;
		else break;
	}
	return pawnsNumber;
}

CaptureGoEngine::CaptureGoEngine() {
	this->blackPawns = 0;
	this->whitePawns = 0;
}

CaptureGoEngine::CaptureGoEngine(unsigned long long blackPawns, unsigned long long whitePawns) {
	this->blackPawns = blackPawns;
	this->whitePawns = whitePawns;
}

CaptureGoEngine::CaptureGoEngine(char *blackPawns, char *whitePawns) {
	this->blackPawns = pawnsFromStringToLong(blackPawns);
	this->whitePawns = pawnsFromStringToLong(whitePawns);
}

bool CaptureGoEngine::isGameOver() {
	// nie mo�e jednoczenie sta� czarny i bia�y na jednym polu
	assert(!(blackPawns & whitePawns));

	// je�li plansza jest pa�na to ostatni gracz zwyci�y�
	if ((blackPawns | whitePawns) == CaptureGoEngine::fullBoardMask)
	{
		possiblyDeadBlackPawns = possiblyDeadWhitePawns = 0;
		return true;
	}
	possiblyDeadBlackPawns = blackPawns;
	possiblyDeadWhitePawns = whitePawns;	
	// sprawdzamy ka�de wolne pole planszy
	unsigned long long i = 1;
	for (int j = 0; j < fieldsNumber; i <<= 1, j++) {
		// szukamy oddech�w (puste pola)
		if (!(blackPawns & i) & !(whitePawns & i))
		{
			// sztucznie (na potrzeby rekurencji) ustawiamy, �e j-te pole jest potencjalnie martwe dla obydwu graczy
			possiblyDeadBlackPawns |= i;
			possiblyDeadWhitePawns |= i;
			checkBreath(i, &possiblyDeadBlackPawns);
			checkBreath(i, &possiblyDeadWhitePawns);
		}
		// czy zosta�y jeszcze potencjalnie martwe pola
		if (!(possiblyDeadBlackPawns | possiblyDeadWhitePawns)) {
			return false;
		}
	}
	return true;
}

void  CaptureGoEngine::checkBreath(unsigned long long checkMask, unsigned long long *possiblyDeadPawns) {
	if (checkMask & *possiblyDeadPawns)
	{
		// je�li mo�emy da� oddech danemu pionowi
		if (*possiblyDeadPawns & checkMask)
		{
			// odznaczamy to �ywe pole z grupy p�l potencjalnie martwych
			*possiblyDeadPawns ^= checkMask;
			// sprawdzamy czy mo�emy da� oddech s�siadowi:
			unsigned long long newCheckMask;
			{
				// po lewej
				newCheckMask = checkMask >> 1;
				if (newCheckMask & CaptureGoEngine::leftBorderMask) {
					checkBreath(newCheckMask, possiblyDeadPawns);
				}
				// po prawej
				newCheckMask = checkMask << 1;
				if (newCheckMask & CaptureGoEngine::rightBorderMask) {
					checkBreath(newCheckMask, possiblyDeadPawns);
				}
				// u g�ry
				newCheckMask = checkMask >> CaptureGoEngine::boardSize;
				if (newCheckMask > 0) {
					checkBreath(newCheckMask, possiblyDeadPawns);
				}
				// na dole
				newCheckMask = checkMask << CaptureGoEngine::boardSize;
				if (newCheckMask <= CaptureGoEngine::endOfBoardMask) {
					checkBreath(newCheckMask, possiblyDeadPawns);
				}
			}
		}
	}
}

void CaptureGoEngine::checkIsItAWinner(bool checkForFirstPlayer, bool *isWinner)
{
	if (checkForFirstPlayer)
	{
		*isWinner = (possiblyDeadBlackPawns) ? false : true;
	}
	else {
		*isWinner = (possiblyDeadWhitePawns) ? false : true;
	}
}

// Zwraca informacj�, czy gracz rozpoczynaj�cy jest zwyci�c�, na podstawie ostatniego wywo�ania isGameOver()
void CaptureGoEngine::checkIsFirstPlayerWinner(bool *isBlackWinner)
{
	if (possiblyDeadBlackPawns && possiblyDeadWhitePawns) *isBlackWinner = nullptr;
	else if (possiblyDeadBlackPawns) *isBlackWinner = false;
	else if (possiblyDeadWhitePawns) *isBlackWinner = true;
	else *isBlackWinner = nullptr;
}

unsigned int CaptureGoEngine::numberOfPossibleMoves(bool)
{
	short res = 0;
	unsigned long long i = 1;
	for (int j = 0; j < fieldsNumber; i <<= 1, j++) {
		if (!((blackPawns & i) | (whitePawns & i))) res++;
	}
	return res;
}

void CaptureGoEngine::GeneratePossibleMoves(CaptureGoEngine* possibleMoves, bool isBlackPlayerTurn)
{	
	short possibleMovesCount = numberOfPossibleMoves(isBlackPlayerTurn);	

	if (isBlackPlayerTurn)
	{
		unsigned long long i = 1;
		for (int j = 0; j < possibleMovesCount; i <<= 1) {
			if (!((blackPawns & i) | (whitePawns & i)))
			{
				possibleMoves[j].blackPawns = blackPawns | i;
				possibleMoves[j].whitePawns = whitePawns;
				j++;
			}
		}
	}
	else
	{
		unsigned long long i = 1;
		for (int j = 0; j < possibleMovesCount; i <<= 1) {
			if (!((blackPawns & i) | (whitePawns & i)))
			{
				possibleMoves[j].blackPawns = blackPawns;
				possibleMoves[j].whitePawns = whitePawns | i;
				j++;
			}
		}
	}
}