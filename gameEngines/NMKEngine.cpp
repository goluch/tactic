#include "NMKEngine.h"
#include <iostream>

using namespace std;
using namespace gameEngines;

int NMKEngine::N;
int NMKEngine::M;
int NMKEngine::K;
bool NMKEngine::ShowNodes = false;

int NMKEngine::border = 1;

NMKEngine::NMKEngine()
{
	emptyFieldsCount = N * M;
	// the board has borders with a thickness of 1
	this->board.resize(N + border * 2, vector<char>(M + border * 2, 0));
	//int N + border = board.size();
	//int M + border = board[0].size();
	// filling boundaries -1 values - so far unnecessary
	/*for (int i = 0; i < M + border; i++) {
		board[0][i] = - 1;
		board[N + border - 1][i] = -1;
	}
	for (int i = 0; i < sizeN; i++) {
		board[i][0] = -1;
		board[i][M + border - 1] = -1;
	}*/
}

//NMKEngine::NMKEngine(NMKEngine& copiedNMKEng)
//{
//	this->emptyFieldsCount = copiedNMKEng.emptyFieldsCount;
//	this->gameOver = copiedNMKEng.gameOver;
//	this->winner = copiedNMKEng.winner;
//	this->board.resize(copiedNMKEng.board.size(), vector<char>(copiedNMKEng.board[0].size(), 0));
//	// copy whole board
//	for (int i = 1; i < N; i++)
//	{
//		for (int j = 1; j < M; j++)
//		{
//			this->board[i][j] = copiedNMKEng.board[i][j];
//		}
//	}
//}

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

int NMKEngine::GeneratePossibleMoves(GameEngine&& possibleMoves, Player activePlayer)
{
	NMKEngine* probablyPossibleMoves = new NMKEngine[this->emptyFieldsCount];
	if (!this->gameOver)
	{
		// for all possible moves
		for (int k = 0; k < this->emptyFieldsCount; k++)
		{
			// copy whole board
			for (int i = 1; i < N + border; i++)
			{
				for (int j = 1; j < M + border; j++)
				{
					probablyPossibleMoves[k].board[i][j] = this->board[i][j];
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
					probablyPossibleMoves[actualPossibleMoveIndex].board[i][j] = (int)activePlayer;
					// update empty fields count
					probablyPossibleMoves[actualPossibleMoveIndex].emptyFieldsCount = this->emptyFieldsCount - 1;

					//cout << probablyPossibleMoves[actualPossibleMoveIndex].GetGameState() << endl;
					// check if someone won after the move
					if (Check_K_InRow(&probablyPossibleMoves[actualPossibleMoveIndex], i, j, activePlayer))
					{
						probablyPossibleMoves[actualPossibleMoveIndex].gameOver = true;
						probablyPossibleMoves[actualPossibleMoveIndex].winner = activePlayer;
						if (activePlayer == Player::first)
						{
							NMKEngine* bestMove = new NMKEngine(probablyPossibleMoves[actualPossibleMoveIndex]);
							delete[] probablyPossibleMoves;
							possibleMoves = (GameEngine&) bestMove;
							return 1;
						}
						actualPossibleMoveIndex++;
						continue;
					}
					// check if bo&ad is full game is over and nobody win
					if (probablyPossibleMoves[actualPossibleMoveIndex].emptyFieldsCount == 0)
					{
						probablyPossibleMoves[actualPossibleMoveIndex].gameOver = true;
						probablyPossibleMoves[actualPossibleMoveIndex].winner = Player::undefined;
						actualPossibleMoveIndex++;
						continue;
					}
					actualPossibleMoveIndex++;
				}
			}
		}
		possibleMoves = (GameEngine&) probablyPossibleMoves;
		return this->emptyFieldsCount;
	}
	return 0;
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

std::string NMKEngine::GetGameState()
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