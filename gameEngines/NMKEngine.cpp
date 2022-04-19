#include "NMKEngine.h"
#include <iostream>

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;
bool NMKEngine::showNodes = false;
bool NMKEngine::cutIfGameOver = false;
string NMKEngine::Info = "";

int NMKEngine::border = 1;

NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	threat = Player::undefined;
	// the board has borders with a thickness of 1
	this->board.resize(N + border * 2, vector<char>(M + border * 2, 0));
	// filling borders with -1 value
	for (int i = 0; i < M + border * 2; i++) {
		board[0][i] = - 1;
		board[N + border][i] = -1;
	}
	for (int i = 0; i < N + border * 2; i++) {
		board[i][0] = -1;
		board[i][M + border] = -1;
	}
}

NMKEngine::~NMKEngine()
{
	board.clear();
}

bool NMKEngine::IsGameOver() {
	return this->gameOver;
}

int NMKEngine::Evaluate(Player activePlayer) {
	if (this->gameOver)
	{
		if (this->winner == Player::undefined)
			return 0;
		if (this->winner == Player::first)
			return 1;
		else
		{
			return -1;
		}
	}
	if (this->threat == activePlayer + 1)
	{
		//cout << this->GetGameState();
		if (this->threat == Player::first)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	// max node
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

GameEngine* NMKEngine::GeneratePossibleMoves(int& generatedMovesCount, Player activePlayer)
{
	if (!this->gameOver)
	{
		NMKEngine* possibleMoves = new NMKEngine[this->emptyFieldsCount];
		// for all possible moves
		for (int k = 0; k < this->emptyFieldsCount; k++)
		{
			// copy whole board
			for (int i = 1; i < N + border; i++)
			{
				for (int j = 1; j < M + border; j++)
				{
					possibleMoves[k].board[i][j] = this->board[i][j];
				}
			}
		}
		int actualPossibleMoveIndex = 0;
		for (int i = 1; i < N + border; i++)
		{
			for (int j = 1; j < M + border; j++)
			{
				// for all possible moves (empty fields)
				if (this->board[i][j] == 0)
				{
					// put active player pawn
					possibleMoves[actualPossibleMoveIndex].board[i][j] = (int)activePlayer;
					// update empty fields count
					possibleMoves[actualPossibleMoveIndex].emptyFieldsCount = this->emptyFieldsCount - 1;

					if (showNodes)
					{
						cout << Info << " " << (int)(activePlayer + 1) << endl << possibleMoves[actualPossibleMoveIndex].GetGameState() << endl;
					}
					// check if someone won after the move
					if (Check_K_InRow(&possibleMoves[actualPossibleMoveIndex], i, j, activePlayer))
					{
						if (cutIfGameOver)
						{
							possibleMoves[0].gameOver = true;
							possibleMoves[0].winner = activePlayer;
							possibleMoves[0].emptyFieldsCount = possibleMoves[actualPossibleMoveIndex].emptyFieldsCount;
							// copy whole board
							for (int i = 1; i < N + border * 2; i++)
							{
								for (int j = 1; j < M + border * 2; j++)
								{
									possibleMoves[0].board[i][j] = possibleMoves[actualPossibleMoveIndex].board[i][j];
								}
							}
							generatedMovesCount = 1;
						}
						else
						{
							possibleMoves[actualPossibleMoveIndex].gameOver = true;
							possibleMoves[actualPossibleMoveIndex].winner = activePlayer;
						}
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
		generatedMovesCount = this->emptyFieldsCount;
		return possibleMoves;
	}
	generatedMovesCount = 0;
	return NULL;
}

bool NMKEngine::Check_K_InRow(NMKEngine* possibleMoves, int i, int j, Player activePlayer)
{
	int nextInRow;
	int foundInRow;
	int foundedThreats = 0;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	if (foundInRow > 1 && foundInRow == K - 1 && foundedThreats == 2)
	{
		if (possibleMoves->threat == Player::undefined)
		{
			//cout << possibleMoves->GetGameState();
			possibleMoves->threat = activePlayer;
		}
	}
	foundedThreats = 0;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i][j - nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i][j + nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	if (foundInRow > 1 && foundInRow == K - 1 && foundedThreats == 2)
	{
		if (possibleMoves->threat == Player::undefined)
		{
			//cout << possibleMoves->GetGameState() << endl;
			possibleMoves->threat = activePlayer;
		}
	}
	foundedThreats = 0;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j - nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j + nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	if (foundInRow > 1 && foundInRow == K - 1 && foundedThreats == 2)
	{
		if (possibleMoves->threat == Player::undefined)
		{
			//cout << possibleMoves->GetGameState();
			possibleMoves->threat = activePlayer;
		}
	}
	foundedThreats = 0;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j - nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j + nextInRow] == (int)Player::undefined)
			{
				foundedThreats++;
			}
			break;
		}
		foundInRow++;
	}
	if (foundInRow == K)
	{
		return true;
	}
	if (foundInRow > 1 && foundInRow == K - 1 && foundedThreats == 2)
	{
		if (possibleMoves->threat == Player::undefined)
		{
			//cout << possibleMoves->GetGameState();
			possibleMoves->threat = activePlayer;
		}
	}
	return false;
}

std::string NMKEngine::GetGameState()
{
	stringstream ss;
	for (int i = 1; i < N + border; i++)
	{
		for (int j = 1; j < M + border; j++)
		{
			ss << (j == 1 ? "" : " ") << (int)board[i][j];
		}
		ss << endl;
	}
	return ss.str();
}

void NMKEngine::SetGameState(std::string newGameState)
{
	std::stringstream ss(newGameState);
	int value;
	this->emptyFieldsCount = 0;
	this->winner = Player::undefined;
	for (int i = 1; i < N + border; i++)
	{
		for (int j = 1; j < M + border; j++)
		{
			ss >> value;
			board[i][j] = value;

			if (value)
			{
				if (Check_K_InRow(this, i, j, (Player)value))
				{
					if (this->winner != Player::undefined)
					{
						throw new exception;
					}
					this->gameOver = true;
					this->winner = (Player)value;
				}
			}
			else
			{
				this->emptyFieldsCount++;
			}
		}
	}
};