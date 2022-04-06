#include "NMKEngine.h"
#include <assert.h>

using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;


NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	activePlayer = 0;
	board = new char*[N];
	for (int i = 0; i < N; i++)
	{
		board[i] = new char[M];
		for (int j = 0; j < M; j++)
		{
			board[i][j] = 0;
		}
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
	return gameOver;
}


unsigned int NMKEngine::numberOfPossibleMoves(bool)
{
	short res = 0;

	return res;
}

GameEngine* NMKEngine::GeneratePossibleMoves()
{
	NMKEngine* possibleMoves = new NMKEngine[emptyFieldsCount];
	int actualPossiblrMoveIndex = 0;
	for (int k = 0; k < emptyFieldsCount; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (board[i][j] == 0)
				{
					possibleMoves[k].board[i][j] = board[i][j];
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (board[i][j] == 0)
			{
				possibleMoves[actualPossiblrMoveIndex++].board[i][j] = 0;
			}
		}
	}
	activePlayer++ % 2;
	return possibleMoves;
}