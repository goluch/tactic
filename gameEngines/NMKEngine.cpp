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
	foundedThreats = 0;
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
	threatIndex.x = -1;
	threatIndex.y = -1;
}

NMKEngine::~NMKEngine()
{
	board.clear();
}

GameEngine* NMKEngine::GeneratePossibleMoves(int& generatedMovesCount, Player activePlayer)
{
	if (!this->gameOver)
	{
		if (this->foundedThreats > 0)
		{
			if (this->foundedThreats > 0)
			{
				throw new exception("too many threats");
			}
			else
			{
				this->emptyFieldsCount = 1;
				NMKEngine* possibleMoves = new NMKEngine[this->emptyFieldsCount];
				// copy whole board
				for (int i = border; i < N + border; i++)
				{
					for (int j = border; j < M + border; j++)
					{
						possibleMoves[0].board[i][j] = this->board[i][j];
					}
				}
				possibleMoves[0].board[threatIndex.x][threatIndex.y] = (int)activePlayer;
			}
		}
		NMKEngine* possibleMoves = new NMKEngine[this->emptyFieldsCount];
		// for all possible moves
		for (int k = 0; k < this->emptyFieldsCount; k++)
		{
			// copy whole board
			for (int i = border; i < N + border; i++)
			{
				for (int j = border; j < M + border; j++)
				{
					possibleMoves[k].board[i][j] = this->board[i][j];
				}
			}
		}
		int actualPossibleMoveIndex = 0;
		for (int i = border; i < N + border; i++)
		{
			for (int j = border; j < M + border; j++)
			{
				// for all possible moves (empty fields)
				if (this->board[i][j] == 0)
				{
					// put active player pawn
					possibleMoves[actualPossibleMoveIndex].board[i][j] = (int)activePlayer;
					// update empty fields count
					possibleMoves[actualPossibleMoveIndex].emptyFieldsCount = this->emptyFieldsCount - 1;
					// check if someone won after the move
					if (Check_K_InRow(&possibleMoves[actualPossibleMoveIndex], i, j, activePlayer))
					{
						if (cutIfGameOver)
						{
							possibleMoves[0].gameOver = true;
							possibleMoves[0].winner = activePlayer;
							possibleMoves[0].emptyFieldsCount = possibleMoves[actualPossibleMoveIndex].emptyFieldsCount;
							// copy whole board
							for (int i = border; i < N + border * 2; i++)
							{
								for (int j = border; j < M + border * 2; j++)
								{
									possibleMoves[0].board[i][j] = possibleMoves[actualPossibleMoveIndex].board[i][j];
								}
							}
							generatedMovesCount = 1;
							if (showNodes)
							{
								for (int i = 0; i < generatedMovesCount; i++)
								{
									cout << Info << " " << (int)(activePlayer + 1) << endl << possibleMoves[i].GetGameState() << endl;
								}
							}
							return possibleMoves;
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
		if (showNodes)
		{
			for (int i = 0; i < generatedMovesCount; i++)
			{
				cout << Info << " " << (int)(activePlayer + 1) << endl << possibleMoves[i].GetGameState() << endl;
			}
		}
		return possibleMoves;
	}
	generatedMovesCount = 0;
	return NULL;
}

bool NMKEngine::Check_K_InRow(NMKEngine* possibleMoves, int i, int j, Player activePlayer)
{
	// Sprawdzamy, czy utworzyliœmy rz¹d pionów o d³ugoœci K
	// Przy okazji sprawdzamy, czy wygenerowaliœmy zagro¿enie
	// Zagro¿enie to wolne pole których po³o¿enie pionka powoduje wygran¹ aktualnego gracza
	// Wystêpuj¹ dwa rodzaje zagro¿eñ:
	// - jedno puste pole wewn¹trz ci¹gu o d³ugoœci K
	// - puste pole b¹dŸ dwa na koñcu ci¹gu o d³ugoœci K - 1
	// Maksymalnie mo¿emy stworzyæ 8 zagro¿eñ ? stawiaj¹c piona w œrodku:
	// ?  ?  ?
	//  x x x
	//   xxx
	// ?xx xx?
	//   xxx
	//  x x x
	// ?  ?  ?
	// Jednak wystarczy zaznaczyæ pierwsze zagro¿enie.
	// Jeœli wystepuj¹ dwa mo¿na oznaczyæ stan jako wygrany.
	// Jeœli doszliœmy do stanu 
	// Jeœli wygenerowaliœmy takie zagro¿enia to zaznaczamy te pola
	// W kolejnym generator wygeneruje mo¿liwe posuniêcia jedynie dla zagro¿onych pól
	int nextInRow;
	int foundInRow;
	bool foundEmptySpace = false;
	int foundedPossibleThreats = 0;
	foundedThreats = 0;
	
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i - nextInRow;
				threatIndex.y = j;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i + nextInRow][j] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i + nextInRow;
				threatIndex.y = j;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	if (foundInRow >= K && !foundEmptySpace)
	{
		return true;
	}
	if (foundInRow >= K - 1 && foundedPossibleThreats > 0)
	{
		if (foundedThreats > 0)
		{
			return true;
		}
		else
		{
			foundedThreats += foundedPossibleThreats;
			//cout << possibleMoves->GetGameState() << endl;
		}
	}

	foundedPossibleThreats = 0;
	foundEmptySpace = false;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i][j - nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i;
				threatIndex.y = j - nextInRow;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i][j + nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i;
				threatIndex.y = j + nextInRow;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	if (foundInRow >= K && !foundEmptySpace)
	{
		return true;
	}
	if (foundInRow >= K - 1 && foundedPossibleThreats > 0)
	{
		if (foundedThreats > 0)
		{
			return true;
		}
		else
		{
			foundedThreats += foundedPossibleThreats;
			//cout << possibleMoves->GetGameState() << endl;
		}
	}

	foundedPossibleThreats = 0;
	foundEmptySpace = false;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (board[i + nextInRow][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j - nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i + nextInRow;
				threatIndex.y = j - nextInRow;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j + nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i - nextInRow;
				threatIndex.y = j + nextInRow;
			}
			else
			{
				break;
			}
		}
		else
		{
			foundInRow++;
		}
	}
	if (foundInRow >= K && !foundEmptySpace)
	{
		return true;
	}
	if (foundInRow >= K - 1 && foundedPossibleThreats > 0)
	{
		if (foundedThreats > 0)
		{
			return true;
		}
		else
		{
			foundedThreats += foundedPossibleThreats;
			//cout << possibleMoves->GetGameState() << endl;
		}
	}

	foundedPossibleThreats = 0;
	foundEmptySpace = false;
	for (foundInRow = 1, nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (board[i + nextInRow][j + nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i + nextInRow][j + nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i + nextInRow;
				threatIndex.y = j + nextInRow;
			}
			else
			{
				break;
			}
		}
		foundInRow++;
	}
	for (nextInRow = 1; nextInRow < K; nextInRow++)
	{
		if (possibleMoves->board[i - nextInRow][j - nextInRow] != (int)activePlayer)
		{
			if (possibleMoves->board[i - nextInRow][j - nextInRow] == (int)Player::undefined)
			{
				if (foundEmptySpace)
				{
					break;
				}
				foundEmptySpace = true;
				foundedPossibleThreats++;
				threatIndex.x = i - nextInRow;
				threatIndex.y = j - nextInRow;
			}
			else
			{
				break;
			}
		}
		foundInRow++;
	}
	if (foundInRow >= K && !foundEmptySpace)
	{
		return true;
	}
	if (foundInRow >= K - 1 && foundedPossibleThreats > 0)
	{
		if (foundedThreats > 0)
		{
			return true;
		}
		else
		{
			foundedThreats += foundedPossibleThreats;
			//cout << possibleMoves->GetGameState() << endl;
		}
	}

	return false;
}

string NMKEngine::GetGameState()
{
	stringstream ss;
	for (int i = border; i < N + border; i++)
	{
		for (int j = border; j < M + border; j++)
		{
			ss << (j == 1 ? "" : " ") << (int)board[i][j];
		}
		ss << endl;
	}
	return ss.str();
}

string NMKEngine::SetGameState(std::istream& ss)
{
	int value;
	this->emptyFieldsCount = 0;
	this->winner = Player::undefined;
	for (int i = border; i < N + border; i++)
	{
		for (int j = border; j < M + border; j++)
		{
			ss >> value;
			board[i][j] = value;

			if (!value)
			{
				this->emptyFieldsCount++;
			}
		}
	}
	for (int i = border; i < N + border; i++)
	{
		for (int j = border; j < M + border; j++)
		{
			if (value)
			{
				if (Check_K_InRow(this, i, j, (Player)value))
				{
					if (this->winner != Player::undefined && this->winner == this->winner + 1)
					{
						throw new exception;
					}
					this->gameOver = true;
					this->winner = (Player)value;
				}
			}
		}
	}
};