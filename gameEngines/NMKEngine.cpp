#include "NMKEngine.h"
#include <assert.h>

using namespace gameEngines;

unsigned int NMKEngine::boardSize;
unsigned int NMKEngine::fieldsNumber;
unsigned int GameEngine::maxPossibleMoves;

unsigned long long NMKEngine::endOfBoardMask;
// maska pól osi¹galnych po ruchu o jedno pole w lewo
// innymi s³owy - posiadaj¹cych po prawej wolne pole (nie granicz¹cymi po prawej z plansz¹)
unsigned long long NMKEngine::leftBorderMask;
// maska pól dozwolonych po ruchu o jedno pole w prawo
// innymi s³owy - posiadaj¹cych po lewej wolne pole (nie granicz¹cymi po lewej z plansz¹)
unsigned long long NMKEngine::rightBorderMask;
// maska wszystkich pól
unsigned long long NMKEngine::fullBoardMask;
// pomocnicze pola wykorzystywane podczas sprawdzania zakoñczenia rozgrywki
unsigned long long NMKEngine::possiblyDeadBlackPawns;
unsigned long long NMKEngine::possiblyDeadWhitePawns;

void NMKEngine::initialize()
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


bool NMKEngine::isGameOver() {
	return true;
}


unsigned int NMKEngine::numberOfPossibleMoves(bool)
{
	short res = 0;
	unsigned long long i = 1;
	for (int j = 0; j < fieldsNumber; i <<= 1, j++) {
		if (!((blackPawns & i) | (whitePawns & i))) res++;
	}
	return res;
}

void NMKEngine::GeneratePossibleMoves(GameEngine* possibleMoves, bool isBlackPlayerTurn)
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