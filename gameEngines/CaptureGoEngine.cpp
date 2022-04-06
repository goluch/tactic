//#include "CaptureGoEngine.h"
//#include <assert.h>
//
//using namespace gameEngines;
//
//
//unsigned long long CaptureGoEngine::endOfBoardMask;
//// maska pól osi¹galnych po ruchu o jedno pole w lewo
//// innymi s³owy - posiadaj¹cych po prawej wolne pole (nie granicz¹cymi po prawej z plansz¹)
//unsigned long long CaptureGoEngine::leftBorderMask;
//// maska pól dozwolonych po ruchu o jedno pole w prawo
//// innymi s³owy - posiadaj¹cych po lewej wolne pole (nie granicz¹cymi po lewej z plansz¹)
//unsigned long long CaptureGoEngine::rightBorderMask;
//// maska wszystkich pól
//unsigned long long CaptureGoEngine::fullBoardMask;
//// pomocnicze pola wykorzystywane podczas sprawdzania zakoñczenia rozgrywki
//unsigned long long CaptureGoEngine::possiblyDeadBlackPawns;
//unsigned long long CaptureGoEngine::possiblyDeadWhitePawns;
//
//void CaptureGoEngine::initialize()
//{
//	CaptureGoEngine::maxPossibleMoves = fieldsNumber = boardSize * boardSize;
//	fullBoardMask = 1;
//	for (int i = 1; i < fieldsNumber; i++)
//	{
//		fullBoardMask <<= 1;
//		fullBoardMask += 1;
//	}
//	endOfBoardMask = 1 << fieldsNumber;
//	if (fieldsNumber == 64) endOfBoardMask = 0;
//	leftBorderMask = rightBorderMask = 0;
//	unsigned long long i = 1;
//	int j = 0;
//	for (unsigned long long i = 1; i != endOfBoardMask; i <<= 1, j++)
//	{
//		if ((j + 1) % boardSize) leftBorderMask |= i;
//		if (j % boardSize) rightBorderMask |= i;
//	}
//	endOfBoardMask--;
//}
//
//unsigned long long CaptureGoEngine::pawnsFromStringToLong(char *pawnsString)
//{
//	unsigned long long pawnsNumber = 0;
//	int j = -1;
//	for (unsigned long long i = 1; i != 0; i <<= 1)
//	{
//		j++;
//		if (pawnsString[j] == '0') continue;
//		else if (pawnsString[j] == '1') pawnsNumber |= i;
//		else break;
//	}
//	return pawnsNumber;
//}
//
//CaptureGoEngine::CaptureGoEngine() {
//	this->blackPawns = 0;
//	this->whitePawns = 0;
//}
//
//CaptureGoEngine::CaptureGoEngine(unsigned long long blackPawns, unsigned long long whitePawns) {
//	this->blackPawns = blackPawns;
//	this->whitePawns = whitePawns;
//}
//
//CaptureGoEngine::CaptureGoEngine(char *blackPawns, char *whitePawns) {
//	this->blackPawns = pawnsFromStringToLong(blackPawns);
//	this->whitePawns = pawnsFromStringToLong(whitePawns);
//}
//
//bool CaptureGoEngine::isGameOver() {
//	// nie mo¿e jednoczenie staæ czarny i bia³y na jednym polu
//	assert(!(blackPawns & whitePawns));
//
//	// jeœli plansza jest pa³na to ostatni gracz zwyciê¿y³
//	if ((blackPawns | whitePawns) == CaptureGoEngine::fullBoardMask)
//	{
//		possiblyDeadBlackPawns = possiblyDeadWhitePawns = 0;
//		return true;
//	}
//	possiblyDeadBlackPawns = blackPawns;
//	possiblyDeadWhitePawns = whitePawns;	
//	// sprawdzamy ka¿de wolne pole planszy
//	unsigned long long i = 1;
//	for (int j = 0; j < fieldsNumber; i <<= 1, j++) {
//		// szukamy oddechów (puste pola)
//		if (!(blackPawns & i) & !(whitePawns & i))
//		{
//			// sztucznie (na potrzeby rekurencji) ustawiamy, ¿e j-te pole jest potencjalnie martwe dla obydwu graczy
//			possiblyDeadBlackPawns |= i;
//			possiblyDeadWhitePawns |= i;
//			checkBreath(i, &possiblyDeadBlackPawns);
//			checkBreath(i, &possiblyDeadWhitePawns);
//		}
//		// czy zosta³y jeszcze potencjalnie martwe pola
//		if (!(possiblyDeadBlackPawns | possiblyDeadWhitePawns)) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void  CaptureGoEngine::checkBreath(unsigned long long checkMask, unsigned long long *possiblyDeadPawns) {
//	if (checkMask & *possiblyDeadPawns)
//	{
//		// jeœli mo¿emy daæ oddech danemu pionowi
//		if (*possiblyDeadPawns & checkMask)
//		{
//			// odznaczamy to ¿ywe pole z grupy pól potencjalnie martwych
//			*possiblyDeadPawns ^= checkMask;
//			// sprawdzamy czy mo¿emy daæ oddech s¹siadowi:
//			unsigned long long newCheckMask;
//			{
//				// po lewej
//				newCheckMask = checkMask >> 1;
//				if (newCheckMask & CaptureGoEngine::leftBorderMask) {
//					checkBreath(newCheckMask, possiblyDeadPawns);
//				}
//				// po prawej
//				newCheckMask = checkMask << 1;
//				if (newCheckMask & CaptureGoEngine::rightBorderMask) {
//					checkBreath(newCheckMask, possiblyDeadPawns);
//				}
//				// u góry
//				newCheckMask = checkMask >> CaptureGoEngine::boardSize;
//				if (newCheckMask > 0) {
//					checkBreath(newCheckMask, possiblyDeadPawns);
//				}
//				// na dole
//				newCheckMask = checkMask << CaptureGoEngine::boardSize;
//				if (newCheckMask <= CaptureGoEngine::endOfBoardMask) {
//					checkBreath(newCheckMask, possiblyDeadPawns);
//				}
//			}
//		}
//	}
//}
//
//void CaptureGoEngine::checkIsItAWinner(bool checkForFirstPlayer, bool *isWinner)
//{
//	if (checkForFirstPlayer)
//	{
//		*isWinner = (possiblyDeadBlackPawns) ? false : true;
//	}
//	else {
//		*isWinner = (possiblyDeadWhitePawns) ? false : true;
//	}
//}
//
//// Zwraca informacjê, czy gracz rozpoczynaj¹cy jest zwyciê¿c¹, na podstawie ostatniego wywo³ania isGameOver()
//void CaptureGoEngine::checkIsFirstPlayerWinner(bool *isBlackWinner)
//{
//	if (possiblyDeadBlackPawns && possiblyDeadWhitePawns) *isBlackWinner = nullptr;
//	else if (possiblyDeadBlackPawns) *isBlackWinner = false;
//	else if (possiblyDeadWhitePawns) *isBlackWinner = true;
//	else *isBlackWinner = nullptr;
//}
//
//unsigned int CaptureGoEngine::numberOfPossibleMoves(bool)
//{
//	short res = 0;
//	unsigned long long i = 1;
//	for (int j = 0; j < fieldsNumber; i <<= 1, j++) {
//		if (!((blackPawns & i) | (whitePawns & i))) res++;
//	}
//	return res;
//}
//
//void CaptureGoEngine::GeneratePossibleMoves(GameEngine* possibleMoves, bool isBlackPlayerTurn)
//{	
//	short possibleMovesCount = numberOfPossibleMoves(isBlackPlayerTurn);	
//
//	if (isBlackPlayerTurn)
//	{
//		unsigned long long i = 1;
//		for (int j = 0; j < possibleMovesCount; i <<= 1) {
//			if (!((blackPawns & i) | (whitePawns & i)))
//			{
//				possibleMoves[j].blackPawns = blackPawns | i;
//				possibleMoves[j].whitePawns = whitePawns;
//				j++;
//			}
//		}
//	}
//	else
//	{
//		unsigned long long i = 1;
//		for (int j = 0; j < possibleMovesCount; i <<= 1) {
//			if (!((blackPawns & i) | (whitePawns & i)))
//			{
//				possibleMoves[j].blackPawns = blackPawns;
//				possibleMoves[j].whitePawns = whitePawns | i;
//				j++;
//			}
//		}
//	}
//}