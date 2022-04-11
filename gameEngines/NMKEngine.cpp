#include "NMKEngine.h"

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;

NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	this->board.resize(N, vector<char>(M, 0));
}

NMKEngine::~NMKEngine()
{
	board.clear();
}

bool NMKEngine::IsGameOver() {
	return this->gameOver;
}

int NMKEngine::Evaluate(Player activePlayer) {
	return 1;
}

int NMKEngine::GetNumberOfPossibleMoves(Player activePlayer)
{
	int res = 0;

	return res;
}

GameEngine* NMKEngine::GeneratePossibleMoves(Player activePlayer)
{
	NMKEngine* possibleMoves = new NMKEngine[this->emptyFieldsCount];
	if (!this->gameOver)
	{
		int actualPossibleMoveIndex = 0;
		for (int k = 0; k < this->emptyFieldsCount; k++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					possibleMoves[k].board[i][j] = this->board[i][j];
				}
			}
			possibleMoves[k].emptyFieldsCount = this->emptyFieldsCount - 1;
			if (!possibleMoves[k].emptyFieldsCount)
			{
				possibleMoves[k].gameOver = true;
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (board[i][j] == 0)
				{
					possibleMoves[actualPossibleMoveIndex++].board[i][j] = (int)activePlayer;
				}
			}
		}
		return possibleMoves;
	}
	return NULL;
}

std::string NMKEngine::PrintGameState()
{
	stringstream ss;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			ss << (j == 0 ? "" : " ") << (int)board[i][j];
		}
		ss << endl;
	}
	return ss.str();
}