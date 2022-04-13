#include "NMKEngine.h"
#include <iostream>

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;
bool NMKEngine::ShowLeafes = false;

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
	// max node
	if (this->gameOver)
	{
		if (NMKEngine::ShowLeafes)
		{
			std::cout << PrintGameState();
		}
		switch (this->winner)
		{
		case Player::first:
			return 1;
		case Player::undefined:
			return 0;
		case Player::second:
		default:
			return -1;
		}
	}
	else if (activePlayer == Player::first)
	{
		return INT_MIN;
	}
	// min node
	else
	{
		return INT_MAX;
	}
}

int NMKEngine::GetNumberOfPossibleMoves(Player activePlayer)
{
	if (this->gameOver)
	{
		return 0;
	}
	else
	{
	return this->emptyFieldsCount;
	}
}

GameEngine* NMKEngine::GeneratePossibleMoves(Player activePlayer)
{
	NMKEngine* possibleMoves = new NMKEngine[this->emptyFieldsCount];
	if (!this->gameOver)
	{
		// for all possible moves
		for (int k = 0; k < this->emptyFieldsCount; k++)
		{
			// copy whole board
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					possibleMoves[k].board[i][j] = this->board[i][j];
				}
			}
		}
		int actualPossibleMoveIndex = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				// for all possible moves (empty fields)
				if (board[i][j] == 0)
				{
					// put active player pawn
					possibleMoves[actualPossibleMoveIndex].board[i][j] = (int)activePlayer;
					// update empty fields count
					possibleMoves[actualPossibleMoveIndex].emptyFieldsCount = this->emptyFieldsCount - 1;
					// check if someone won after the move
					if (Check_K_InRow(&possibleMoves[actualPossibleMoveIndex], i, j, activePlayer))
					{
						actualPossibleMoveIndex++;
						continue;
					}
					// check if bo&ad is full game is over and nobody win
					if (!possibleMoves[actualPossibleMoveIndex].emptyFieldsCount)
					{
						possibleMoves[actualPossibleMoveIndex].gameOver = true;
						possibleMoves[actualPossibleMoveIndex].winner = Player::undefined;
					}
					actualPossibleMoveIndex++;
				}
			}
		}
		return possibleMoves;
	}
	return NULL;
}

bool NMKEngine::Check_K_InRow(NMKEngine* possibleMoves, int i, int j, Player activePlayer)
{
	int nextInRow;
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (i - nextInRow < 0 ||
			possibleMoves->board[i - nextInRow][j] != (int)activePlayer)
		{
			break;
		}
	}
	if (nextInRow == K)
	{
		possibleMoves->gameOver = true;
		possibleMoves->winner = activePlayer;
		return true;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (i + nextInRow >= N ||
			possibleMoves->board[i + nextInRow][j] != (int)activePlayer)
		{
			break;
		}
	}
	if (nextInRow == K)
	{
		possibleMoves->gameOver = true;
		possibleMoves->winner = activePlayer;
		return true;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (j - nextInRow < 0 ||
			possibleMoves->board[i][j - nextInRow] != (int)activePlayer)
		{
			break;
		}
	}
	if (nextInRow == K)
	{
		possibleMoves->gameOver = true;
		possibleMoves->winner = activePlayer;
		return true;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (j + nextInRow >= M ||
			possibleMoves->board[i][j + nextInRow] != (int)activePlayer)
		{
			break;
		}
	}
	if (nextInRow == K)
	{
		possibleMoves->gameOver = true;
		possibleMoves->winner = activePlayer;
		return true;
	}
	return false;
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