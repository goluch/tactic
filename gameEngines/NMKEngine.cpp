#include <assert.h>
#include <vector>
#include "NMKEngine.h"

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;

NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	activePlayer = Player::first;
	vector<vector<int>> board;

	for (int i = 0; i < emptyFieldsCount; i++)
	{
		for (int j = 0; j < M; j++)
		{
			board[i][j] = (char)0;
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

bool NMKEngine::IsGameOver() {
	return gameOver;
}

int NMKEngine::Evaluate() {
	return 1;
}

int NMKEngine::GetNumberOfPossibleMoves()
{
	int res = 0;

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
	//activePlayer++;
	//activePlayer++;
	return possibleMoves;
}