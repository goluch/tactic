#include "NMKEngine.h"
#include <iostream>

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;
int NMKEngine::sizeN;
int NMKEngine::sizeM;
bool NMKEngine::ShowLeafes = false;

int NMKEngine::border = 1;

NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	// the board has borders with a thickness of 1
	this->board.resize(N + border * 2, vector<char>(M + border * 2, 0));
	sizeN = this->board.size() - 1;
	sizeM = this->board[0].size() - 1;
	//int sizeN = board.size();
	//int sizeM = board[0].size();
	// filling boundaries -1 values - so far unnecessary
	/*for (int i = 0; i < sizeM; i++) {
		board[0][i] = - 1;
		board[sizeN - 1][i] = -1;
	}
	for (int i = 0; i < sizeN; i++) {
		board[i][0] = -1;
		board[i][sizeM - 1] = -1;
	}*/
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
			std::cout << PrintGameState() << endl;
		}
		if (this->winner == Player::undefined)
			return 0;
		if (this->winner == activePlayer)
			return 1;
		else
		{
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
			for (int i = 1; i < sizeN; i++)
			{
				for (int j = 1; j < sizeM; j++)
				{
					possibleMoves[k].board[i][j] = this->board[i][j];
				}
			}
		}
		int actualPossibleMoveIndex = 0;
		for (int i = 1; i < sizeN; i++)
		{
			for (int j = 1; j < sizeM; j++)
			{
				// for all possible moves (empty fields)
				if (this->board[i][j] == 0)
				{
					// put active player pawn
					possibleMoves[actualPossibleMoveIndex].board[i][j] = (int)activePlayer;
					// update empty fields count
					possibleMoves[actualPossibleMoveIndex].emptyFieldsCount = this->emptyFieldsCount - 1;

					cout << possibleMoves[actualPossibleMoveIndex].PrintGameState() << endl;
					// check if someone won after the move
					if (Check_K_InRow(&possibleMoves[actualPossibleMoveIndex], i, j, activePlayer))
					{
						possibleMoves[actualPossibleMoveIndex].emptyFieldsCount = 0;
						possibleMoves[actualPossibleMoveIndex].gameOver = true;
						possibleMoves[actualPossibleMoveIndex].winner = activePlayer;
						actualPossibleMoveIndex++;
						continue;
					}
					// check if bo&ad is full game is over and nobody win
					if (possibleMoves[actualPossibleMoveIndex].emptyFieldsCount == 0)
					{
						possibleMoves[actualPossibleMoveIndex].gameOver = true;
						possibleMoves[actualPossibleMoveIndex].winner = Player::undefined;
						actualPossibleMoveIndex++;
						continue;
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
	int foundInRow;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j - nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j + nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j - nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j + nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j - nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j + nextInRow] != (int)activePlayer)
		{
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	return false;
}

std::string NMKEngine::PrintGameState()
{
	stringstream ss;
	for (int i = 1; i < board.size() - 1; i++)
	{
		for (int j = 1; j < board[0].size() - 1; j++)
		{
			ss << (j == 1 ? "" : " ") << (int)board[i][j];
		}
		ss << endl;
	}
	return ss.str();
}