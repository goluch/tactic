#include "NMKEngine.h"
#include <assert.h>

using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;

unsigned long long NMKEngine::endOfBoardMask;
// maska p�l osi�galnych po ruchu o jedno pole w lewo
// innymi s�owy - posiadaj�cych po prawej wolne pole (nie granicz�cymi po prawej z plansz�)
unsigned long long NMKEngine::leftBorderMask;
// maska p�l dozwolonych po ruchu o jedno pole w prawo
// innymi s�owy - posiadaj�cych po lewej wolne pole (nie granicz�cymi po lewej z plansz�)
unsigned long long NMKEngine::rightBorderMask;
// maska wszystkich p�l
unsigned long long NMKEngine::fullBoardMask;
// pomocnicze pola wykorzystywane podczas sprawdzania zako�czenia rozgrywki
unsigned long long NMKEngine::possiblyDeadBlackPawns;
unsigned long long NMKEngine::possiblyDeadWhitePawns;


NMKEngine::NMKEngine()
{
	board = new char*[N];
	for (int i = 0; i < N; i++)
	{
		board[i] = new char[M];
	}
}

NMKEngine::~NMKEngine()
{
	for (int i = 0; i < N; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}


bool NMKEngine::isGameOver() {
	return true;
}


unsigned int NMKEngine::numberOfPossibleMoves(bool)
{
	short res = 0;

	return res;
}

void NMKEngine::GeneratePossibleMoves(GameEngine* possibleMoves, bool isBlackPlayerTurn)
{	
	short possibleMovesCount = numberOfPossibleMoves(isBlackPlayerTurn);	

	if (isBlackPlayerTurn)
	{
	}
}