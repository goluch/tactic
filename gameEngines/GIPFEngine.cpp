#include <utility>
#include <algorithm>
#include "GIPFEngine.h"
#include "GameEngineExceptions.h"

using namespace gameEngines;

const char GIPFEngine::firstPlayerField = 'W';
const char GIPFEngine::secondPlayerField = 'B';
const char GIPFEngine::startField = '+';
const char GIPFEngine::emptyField = '_';
const char GIPFEngine::forbiddenField = '!';
vector<pair<Coord, Coord>> GIPFEngine::allMoves;

GIPFEngine& GIPFEngine::operator=(GIPFEngine g)
{
	ClearAndAssign(g);
	return *this;
}

void GIPFEngine::ClearAndAssign(GIPFEngine const& g)
{
	ClearGameState();
	this->activePlayer = g.activePlayer;
	this->board = g.board;
	this->collisionIndex = g.collisionIndex;
	this->diag = g.diag;
	this->s = g.s;
	this->k = g.k;
	this->gw = g.gw;
	this->gw_res = g.gw_res;
	this->gb = g.gb;
	this->gb_res = g.gb_res;
	this->emptyFieldsLeft = g.emptyFieldsLeft;
	this->collisionInKInRowsNumber = g.collisionInKInRowsNumber;
	this->kInRowsconflictingRows[0] = g.kInRowsconflictingRows[0];
	this->kInRowsconflictingRows[1] = g.kInRowsconflictingRows[1];
	this->kInRowsconflictingRows[2] = g.kInRowsconflictingRows[2];
	this->gameOver = g.gameOver;
	this->winner = g.winner;
}

bool GIPFEngine::operator==(GIPFEngine const& g)
{
	if (activePlayer != g.activePlayer) return false;
	if (board != g.board) return false;
	if (collisionIndex != g.collisionIndex) return false;
	if (collisionInKInRowsNumber != g.collisionInKInRowsNumber) return false;
	if (diag != g.diag) return false;
	if (s != g.s) return false;
	if (k != g.k) return false;
	if (gw != g.gw) return false;
	if (gw_res != g.gw_res) return false;
	if (gb != g.gb) return false;
	if (gb_res != g.gb_res) return false;
	if (emptyFieldsLeft != g.emptyFieldsLeft) return false;
	return true;
}

bool GIPFEngine::operator!=(GIPFEngine const& g)
{
	return !(*this == g);
}

GIPFEngine::GIPFEngine()
{
	ClearGameState();
}

GIPFEngine::GIPFEngine(GIPFEngine& g)
{
	ClearAndAssign(g);
}

GIPFEngine::~GIPFEngine()
{ }

GameEngine* GIPFEngine::GeneratePossibleMoves(int& count, Player activePlayer)
{
	GIPFEngine* newGameState = new GIPFEngine[this->allMoves.size()];
	string result;
	count = 0;
	for (pair<Coord, Coord> possibleMove : this->allMoves)
	{
		newGameState[count] = *this;
		int movesCount = 0;
		result = newGameState[count].DoMoveWithoutRemovingRows(possibleMove.first, possibleMove.second);
		if (result == "MOVE_COMMITTED")
		{
			if (newGameState[count].collisionInKInRowsNumber > 0)
			{
				int i = newGameState[count].collisionInKInRowsNumber;
				while (i--)
				{
					newGameState[count + 1] = newGameState[count];
					newGameState[count].RemoveKInRows(result, i);
					if (cutIfGameOver && newGameState[count].IsGameOver())
					{
						//if (newGameState[count].Evaluate(newGameState[count].activePlayer) == -1)
						{
							count = 1;
							newGameState[0] = newGameState[count];
						}
					}
					int prevCount = count;
					bool foundDuplicate = false;
					while (prevCount--)
					{
						if (newGameState[prevCount] == newGameState[count])
						{
							foundDuplicate = true;
							newGameState[count] = newGameState[count + 1];
							break;
						}
					}
					if (!foundDuplicate)
					{
						count++;
					}
				}
			}
			else
			{
				newGameState[count].RemoveKInRows(result);
				if (cutIfGameOver && newGameState[count].IsGameOver())
				{
					//if (newGameState[count].Evaluate(newGameState[count].activePlayer) == -1)
					{
						count = 1;
						newGameState[0] = newGameState[count];
					}
				}
				int prevCount = count;
				bool foundDuplicate = false;
				while (prevCount--)
				{
					if (newGameState[prevCount] == newGameState[count])
					{
						foundDuplicate = true;
						break;
					}
				}
				if (!foundDuplicate)
				{
					count++;
				}
			}
		}
	}
	return newGameState;
}

string GIPFEngine::GetGameState()
{
	if (board.size() == 0)
	{
		return "EMPTY_BOARD";
	}
	stringstream ss;
	ss << this->s << " " << this->k << " " << this->gw << " " << this->gb << endl;
	ss << this->gw_res << " " << this->gb_res << " " << (activePlayer == Player::first ? firstPlayerField : secondPlayerField) << endl;
	for (int i = 1; i < diag - 1; i++)
	{
		int spacesPrefix = s - i;
		while (spacesPrefix-- > 0)
		{
			ss << ' ';
		}
		for (int j = 0; j < diag; j++)
		{
			if (j > 1)
			{
				ss << " ";
			}
			switch (board[i][j])
			{
			case firstPlayerField:
				ss << firstPlayerField;
				break;
			case secondPlayerField:
				ss << secondPlayerField;
				break;
			case emptyField:
				ss << emptyField;
				break;
			case startField:
				break;
			}

		}
		ss << endl;
	}
	return ss.str();
}

Coord GIPFEngine::ConvertCoordinates(string Coordinates)
{
	int i = static_cast<int>(Coordinates[1]) - static_cast<int>('1');
	int j = static_cast<int>(Coordinates[0]) - static_cast<int>('a');
	i = diag - 1 - i;
	if (j < s)
	{
		i-= (s - j);
	}
	return Coord(i, j);
}

Direction GIPFEngine::SpecifyDirection(Coord sour, Coord dest)
{
	if (sour.second == dest.second)
	{
		if (sour.first == dest.first - 1)
		{
			return S;
		}
		if (sour.first == dest.first + 1)
		{
			return N;
		}
		return Unknown;
	}
	if (sour.first == dest.first)
	{
		if (sour.second == dest.second - 1)
		{
			return E;
		}
		if (sour.second == dest.second + 1)
		{
			return W;
		}
		return Unknown;
	}
	if (sour.first == dest.first - 1 && sour.second == dest.second - 1)
	{
		return SE;
	}
	if (sour.first == dest.first + 1 && sour.second == dest.second + 1)
	{
		return NW;
	}
	return Unknown;
}

Direction GIPFEngine::GetOppositeDirection(Direction moveDir)
{
	switch (moveDir)
	{
	case E:
		return W;
	case S:
		return N;
	case SE:
		return NW;
	case W:
		return E;
	case N:
		return S;
	case NW:
		return SE;
	case Unknown:
		return Unknown;
	}
	return Unknown;
}

Coord GIPFEngine::SpecifyNextFieldCoord(Coord sour, Direction moveDir)
{
	switch (moveDir)
	{
	case E:
		sour.second++;
		return sour;
	case S:
		sour.first++;
		return sour;
	case SE:
		sour.first++;
		sour.second++;
		return sour;
	case W:
		sour.second--;
		return sour;
	case N:
		sour.first--;
		return sour;
	case NW:
		sour.first--;
		sour.second--;
		return sour;
	}
	return Coord(-1, -1);
}

bool GIPFEngine::MoveWholeRow(Coord sour, Coord dest, Direction moveDir)
{
	while (sour != dest)
	{
		Coord prev = SpecifyNextFieldCoord(dest, GetOppositeDirection(moveDir));
		if (board[prev.first][prev.second] == startField)
		{
			board[dest.first][dest.second] = activePlayer == Player::first ? firstPlayerField : secondPlayerField;
			if (activePlayer == Player::first)
			{
				this->gw_res--;
			}
			else
			{
				this->gb_res--;
			}
			if (sour == prev)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		board[dest.first][dest.second] = board[prev.first][prev.second];
		dest = prev;
	}
	return false;
}

string GIPFEngine::DoMoveWithoutRemovingRows(Coord sour, Coord dest)
{
	Direction moveDir = SpecifyDirection(sour, dest);
	if (moveDir == Unknown)
	{
		return "UNKNOWN_MOVE_DIRECTION";
	}
	while (this->board[dest.first][dest.second] != emptyField)
	{
		switch (this->board[dest.first][dest.second])
		{
		case firstPlayerField:
			dest = SpecifyNextFieldCoord(dest, moveDir);
			break;
		case secondPlayerField:
			dest = SpecifyNextFieldCoord(dest, moveDir);
			break;
		case startField:
			return "BAD_MOVE_ROW_IS_FULL";
		default:
			throw WrongGameStateSettingsException("BAD_MOVE_UNKNOWWN_FIELD_STATE");
		}
	}
	if (!MoveWholeRow(sour, dest, moveDir))
	{
		throw WrongGameStateSettingsException("UNABLE_TO_MOVE_WHOLE_ROW");
	}
	int KInRowFoundNumber = CheckKInRow();
	this->emptyFieldsLeft--;
	this->activePlayer++;
	return "MOVE_COMMITTED";
}

string GIPFEngine::DoMove(Coord sour, Coord dest)
{
	string res = DoMoveWithoutRemovingRows(sour, dest);
	if (res == "MOVE_COMMITTED")
	{
		string removedInfo;
		int removedRows = RemoveKInRows(removedInfo);
		if (removedInfo != "")
		{
			return removedInfo;
		}
		emptyFieldsLeft--;
		CheckForGameOver();
		return "MOVE_COMMITTED";
	}
	else
	{
		return res;
	}
}

string GIPFEngine::DoMove(string move)
{
	Coord sour = ConvertCoordinates(move.substr(0, 2));
	if (sour.first > diag - 1 || sour.second > diag - 1 || this->board[sour.first][sour.second] == '!')
	{
		return "BAD_MOVE_" + move.substr(0, 2) + "_IS_WRONG_INDEX";
	}
	if (this->board[sour.first][sour.second] != '+')
	{
		return "BAD_MOVE_" + move.substr(0, 2) + "_IS_WRONG_STARTING_FIELD";
	}
	Coord dest = ConvertCoordinates(move.substr(3));
	if (dest.first > diag - 1 || dest.second > diag - 1 || this->board[sour.first][sour.second] == '!')
	{
		return "BAD_MOVE_" + move.substr(3) + "_IS_WRONG_INDEX";
	}
	if (this->board[dest.first][dest.second] != '_' &&
		this->board[dest.first][dest.second] != 'W' &&
		this->board[dest.first][dest.second] != 'B')
	{
		return "BAD_MOVE_" + move.substr(3) + "_IS_WRONG_DESTINATION_FIELD";
	}
	return DoMove(sour, dest);
}

void GIPFEngine::ClearGameState()
{
	board.clear();
	this->kInRowsconflictingRows[0] = NULL;
	this->kInRowsconflictingRows[1] = NULL;
	this->kInRowsconflictingRows[2] = NULL;
	this->collisionInKInRowsNumber = 0;
	this->winner = Player::undefined;
	this->gameOver = false;
	this->emptyFieldsLeft = 0;
}

string GIPFEngine::SetGameState(istream& newGameState)
{
	ClearGameState();
	newGameState >> s >> k >> gw >> gb;
	newGameState >> gw_res;
	if (gw_res > gw)
	{
		board.clear();
		return "WRONG_WHITE_PAWNS_NUMBER";
	};
	newGameState >> gb_res;
	if (gb_res > gb)
	{
		board.clear();
		return "WRONG_BLACK_PAWNS_NUMBER";
	};
	newGameState >> value;
	switch (value)
	{
	case firstPlayerField:
		activePlayer = Player::first;
		break;
	case secondPlayerField:
		activePlayer = Player::second;
		break;
	default:
		board.clear();
		return "UNKNOWN_ACTIVE_PLAYER";
	}
	diag = s * 2 - 1 + border * 2;
	this->board.resize(diag, vector<char>(diag));
	while (cin.peek() == '\n')
	{
		cin.get(value);
	}
	for (int i = 0; i < diag; i++)
	{
		for (int j = 0; j < diag; j++)
		{
			if (cin.peek() == '\n')
			{
				cin.get(value);
				if (i > 0 && i < diag - 1)
				{
					if (i + s < diag - 1)
					{
						if (j != i + s)
						{
							board.clear();
							return "WRONG_BOARD_ROW_LENGTH";
						}
					}
					else
					{
						if (j != diag - 1)
						{
							board.clear();
							return "WRONG_BOARD_ROW_LENGTH";
						}
					}
				}
			}
			if (j > s + i || i > s + j)
			{
				board[i][j] = forbiddenField;
				continue;
			}
			if (i == 0 || j == 0 || i == diag - 1 || j == diag - 1 || j == s + i || i == s + j)
			{
				board[i][j] = startField;
				continue;
			}
			newGameState >> value;
			if (value == emptyField)
			{
				emptyFieldsLeft++;
			}
			board[i][j] = value;
		}
	}
	if (value != '\n')
	{
		board.clear();
		return "WRONG_BOARD_ROW_LENGTH";
	}
	ComputeAllMoves();
	CheckForGameOver();
	return "OK";
}

//int GIPFEngine::CheckKInRow(Coord checkedField)
//{
//	char searchedColor = board[checkedField.first][checkedField.second];
//	int foundedKINRows = 0;
//	int foundedFieldsNumber = 1;
//	for (int dir = E; dir != W; dir++)
//	{
//		Coord nextField = checkedField;
//		do
//		{
//			nextField = SpecifyNextFieldCoord(nextField, static_cast<Direction>(dir));
//			if (board[nextField.first][nextField.second] == searchedColor)
//			{
//				foundedFieldsNumber++;
//				if (foundedFieldsNumber == k)
//				{
//					foundedKINRows++;
//					continue;
//				}
//			}
//			else
//			{
//				foundedFieldsNumber = 1;
//				continue;
//			}
//		} while (board[nextField.first][nextField.second] == searchedColor);
//		Direction oppositeDir = GetOppositeDirection(static_cast<Direction>(dir));
//		do
//		{
//			nextField = SpecifyNextFieldCoord(nextField, oppositeDir);
//			if (board[nextField.first][nextField.second] == searchedColor)
//			{
//				foundedFieldsNumber++;
//				if (foundedFieldsNumber == k)
//				{
//					foundedKINRows++;
//					continue;
//				}
//			}
//			else
//			{
//				foundedFieldsNumber = 1;
//				continue;
//			}
//		} while (board[nextField.first][nextField.second] == searchedColor);
//	}
//	return foundedKINRows;
//}

bool GIPFEngine::GetPawnColor(Coord fieldCoord, char& actualColor) {
	switch (board[fieldCoord.first][fieldCoord.second])
	{
	case firstPlayerField:
	case secondPlayerField:
		actualColor = board[fieldCoord.first][fieldCoord.second];
		return true;
	default:
		actualColor = '?';
		return false;
	}
}

int GIPFEngine::AddToKInRowsAndFindCollision(KInRow possiblekInRowsIndexes)
{
	vector<Coord> v_intersection;
	// todo: jeœli koliduj¹ trzy rzêdy to dwa koliduj¹ce juz s¹ w kInRowsconflictingRows
	for (vector<KInRow>::iterator kInRow = kInRowsIndexes.begin(); kInRow != kInRowsIndexes.end(); ++kInRow)
	{
	    set_intersection(kInRow->row.begin(), kInRow->row.end(), possiblekInRowsIndexes.row.begin(), possiblekInRowsIndexes.row.end(), back_inserter(v_intersection));
		if (v_intersection.size())
		{
			this->collisionIndex = v_intersection.front();
			this->kInRowsconflictingRows[0] = new KInRow(possiblekInRowsIndexes);
			this->kInRowsconflictingRows[1] = new KInRow(*kInRow);
			this->kInRowsIndexes.erase(kInRow);
			this->collisionInKInRowsNumber = 2;
			return v_intersection.size();
		}
	}
	if (kInRowsconflictingRows[0] != NULL)
	{
		set_intersection(kInRowsconflictingRows[0]->row.begin(), kInRowsconflictingRows[0]->row.end(), possiblekInRowsIndexes.row.begin(), possiblekInRowsIndexes.row.end(), back_inserter(v_intersection));
		set_intersection(kInRowsconflictingRows[1]->row.begin(), kInRowsconflictingRows[1]->row.end(), possiblekInRowsIndexes.row.begin(), possiblekInRowsIndexes.row.end(), back_inserter(v_intersection));
		if (v_intersection.size())
		{
			this->kInRowsconflictingRows[2] = new KInRow(possiblekInRowsIndexes);
			this->collisionInKInRowsNumber = 3;
			return 0;
		}
	}
	this->kInRowsIndexes.push_back(possiblekInRowsIndexes);
	return 0;
}

int GIPFEngine::CheckHorizontallyOrVertically(Direction iDir, Direction jDir)
{
	KInRow possiblekInRowsIndexes(jDir);
	char actualColor;
	bool foundKInRow = false;
	int foundKInRows = 0;
	int foundSameInRow;
	for (Coord i = Coord(1, 1); i.first < diag - 1 && i.second < diag - 1; i = SpecifyNextFieldCoord(i, iDir))
	{
		if (foundKInRow)
		{
			foundKInRows++;
			AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
			foundKInRow = false;
		}
		possiblekInRowsIndexes.row.clear();
		foundSameInRow = (GetPawnColor(i, actualColor)) ? 1 : 0;
		if (foundSameInRow)
		{
			possiblekInRowsIndexes.row.push_back(i);
		}
		for (Coord j = SpecifyNextFieldCoord(i, static_cast<Direction>(jDir)); j.first < diag - 1 && j.second < diag - 1; j = SpecifyNextFieldCoord(j, jDir))
		{
			if (board[j.first][j.second] == actualColor)
			{
				possiblekInRowsIndexes.row.push_back(j);
				foundSameInRow++;
				if (foundSameInRow >= k)
				{
					foundKInRow = true;
				}
			}
			else
			{
				if (foundKInRow)
				{
					foundKInRows++;
					AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
					foundKInRow = false;
				}
				possiblekInRowsIndexes.row.clear();
				foundSameInRow = (GetPawnColor(j, actualColor)) ? 1 : 0;
				if (foundSameInRow)
				{
					possiblekInRowsIndexes.row.push_back(j);
				}
			}
		}
	}
	return foundKInRows;
}

int GIPFEngine::CheckDiagonally(Direction iDir1, Direction iDir2, Direction jDir)
{
	KInRow possiblekInRowsIndexes(jDir);
	char actualColor;
	bool foundKInRow = false;
	int foundKInRows = 0;
	int foundSameInRow;
	for (Coord i = Coord(1, s); i.first < diag && i.second > 0; i = SpecifyNextFieldCoord(i, iDir1))
	{
		if (foundKInRow)
		{
			foundKInRows++;
			AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
			foundKInRow = false;
		}
		possiblekInRowsIndexes.row.clear();
		foundSameInRow = (GetPawnColor(i, actualColor)) ? 1 : 0;
		if (foundSameInRow)
		{
			possiblekInRowsIndexes.row.push_back(i);
		}
		for (Coord j = SpecifyNextFieldCoord(i, static_cast<Direction>(jDir)); j.first < diag - 1 && j.second < diag - 1; j = SpecifyNextFieldCoord(j, jDir))
		{
			if (board[j.first][j.second] == actualColor)
			{
				possiblekInRowsIndexes.row.push_back(j);
				foundSameInRow++;
				if (foundSameInRow >= k)
				{
					foundKInRow = true;
				}
			}
			else
			{
				if (foundKInRow)
				{
					foundKInRows++;
					AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
					foundKInRow = false;
				}
				possiblekInRowsIndexes.row.clear();
				foundSameInRow = (GetPawnColor(j, actualColor)) ? 1 : 0;
				if (foundSameInRow)
				{
					possiblekInRowsIndexes.row.push_back(j);
				}
			}
		}
	}
	for (Coord i = Coord(2, 1); i.first < diag - 1 && i.second < diag - 1; i = SpecifyNextFieldCoord(i, iDir2))
	{
		if (foundKInRow)
		{
			foundKInRows++;
			AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
			foundKInRow = false;
		}
		possiblekInRowsIndexes.row.clear();
		foundSameInRow = (GetPawnColor(i, actualColor)) ? 1 : 0;
		if (foundSameInRow)
		{
			possiblekInRowsIndexes.row.push_back(i);
		}
		for (Coord j = SpecifyNextFieldCoord(i, static_cast<Direction>(jDir)); j.first < diag - 1 && j.second < diag - 1; j = SpecifyNextFieldCoord(j, jDir))
		{
			if (board[j.first][j.second] == actualColor)
			{
				possiblekInRowsIndexes.row.push_back(j);
				foundSameInRow++;
				if (foundSameInRow == k)
				{
					foundKInRow = true;
				}
			}
			else
			{
				if (foundKInRow)
				{
					foundKInRows++;
					AddToKInRowsAndFindCollision(possiblekInRowsIndexes);
					foundKInRow = false;
				}
				possiblekInRowsIndexes.row.clear();
				foundSameInRow = (GetPawnColor(j, actualColor)) ? 1 : 0;
				if (foundSameInRow)
				{
					possiblekInRowsIndexes.row.push_back(j);
				}
			}
		}
	}
	return foundKInRows;
}

int GIPFEngine::CheckKInRow()
{
	this->collisionInKInRowsNumber = 0;
	int foundKInRows = 0;
	kInRowsIndexes.clear();
	foundKInRows += CheckHorizontallyOrVertically(E, S);
	foundKInRows += CheckHorizontallyOrVertically(S, E);
	foundKInRows += CheckDiagonally(W, S, SE);
	return foundKInRows;
}

bool GIPFEngine::UpdatePlayersReserves(Coord tmpCoord, char kInRowColor)
{
	char fieldColor = this->board[tmpCoord.first][tmpCoord.second];
	if (fieldColor == firstPlayerField || fieldColor == secondPlayerField)
	{
		this->board[tmpCoord.first][tmpCoord.second] = emptyField;
		switch (kInRowColor)
		{
		case firstPlayerField:
			if (fieldColor == firstPlayerField)
			{
				gw_res++;
				emptyFieldsLeft++;
			}
			return true;
		case secondPlayerField:
			if (fieldColor == secondPlayerField)
			{
				gb_res++;
				emptyFieldsLeft++;
			}
			return true;
		default:
			throw WrongGameStateSettingsException("Bad kInRowColor color");
		}
	}
	else
	{
		return false;
	}
}

bool GIPFEngine::RemoveKinRow(KInRow* kInRow)
{
	bool cont = true;
	Coord tmpCoord = kInRow->row.front();
	char kInRowColor = board[tmpCoord.first][tmpCoord.second];
	do
	{
		tmpCoord = SpecifyNextFieldCoord(tmpCoord, GetOppositeDirection(kInRow->dir));
		cont = UpdatePlayersReserves(tmpCoord, kInRowColor);
	} while (cont);
	for (Coord i : kInRow->row)
	{
		cont = UpdatePlayersReserves(i, kInRowColor);
	}
	cont = true;
	tmpCoord = kInRow->row.back();
	do
	{
		tmpCoord = SpecifyNextFieldCoord(tmpCoord, kInRow->dir);
		cont = UpdatePlayersReserves(tmpCoord, kInRowColor);
	} while (cont);
	return false;
}

int GIPFEngine::RemoveKInRows(string& errorInfo, int rowToRemove)
{
	// raczej istnienie wiêcej ni¿ jednej kolizjii nie jest mo¿liwe podczas normalnej gry wiêc mo¿na z czasem zamieniæ na bool.
	int removedConflictingRowsCount = 0;
	if (rowToRemove == -1)
	{
		if (this->collisionInKInRowsNumber)
		{
			string removingPlayerColor;
			cin >> removingPlayerColor;
			switch (board[this->collisionIndex.first][this->collisionIndex.second])
			{
			case firstPlayerField:
				if (removingPlayerColor.compare("b:") == 0)
				{
					errorInfo = "WRONG_COLOR_OF_CHOSEN_ROW";
					return 0;
				}
				break;
			case secondPlayerField:
				if (removingPlayerColor.compare("w:") == 0)
				{
					errorInfo = "WRONG_COLOR_OF_CHOSEN_ROW";
					return 0;
				}
				break;
			default:
				throw WrongGameStateSettingsException("UNKNOWN_COLOR_CHOSEN_ROW");
				break;
			}
			string removingRowBeginIndex;
			string removingRowEndIndex;
			cin >> removingRowBeginIndex;
			cin >> removingRowEndIndex;
			Coord RowBeginIndex = ConvertCoordinates(removingRowBeginIndex);
			Coord RowEndIndex = ConvertCoordinates(removingRowEndIndex);

			if (this->kInRowsconflictingRows[0] != NULL)
				if (this->kInRowsconflictingRows[0]->row.front() == RowBeginIndex &&
					this->kInRowsconflictingRows[0]->row.back() == RowEndIndex ||
					this->kInRowsconflictingRows[0]->row.front() == RowEndIndex &&
					this->kInRowsconflictingRows[0]->row.back() == RowBeginIndex)
				{
					RemoveKinRow(this->kInRowsconflictingRows[0]);
					removedConflictingRowsCount++;
				}
			if (this->kInRowsconflictingRows[1] != NULL)
				if (this->kInRowsconflictingRows[1]->row.front() == RowBeginIndex &&
					this->kInRowsconflictingRows[1]->row.back() == RowEndIndex ||
					this->kInRowsconflictingRows[1]->row.front() == RowEndIndex &&
					this->kInRowsconflictingRows[1]->row.back() == RowBeginIndex)
				{
					RemoveKinRow(this->kInRowsconflictingRows[1]);
					removedConflictingRowsCount++;
				}
			if (this->kInRowsconflictingRows[2] != NULL)
				if (this->kInRowsconflictingRows[2]->row.front() == RowBeginIndex &&
					this->kInRowsconflictingRows[2]->row.back() == RowEndIndex ||
					this->kInRowsconflictingRows[2]->row.front() == RowEndIndex &&
					this->kInRowsconflictingRows[2]->row.back() == RowBeginIndex)
				{
					RemoveKinRow(this->kInRowsconflictingRows[2]);
					removedConflictingRowsCount++;
				}
			if (!removedConflictingRowsCount)
			{
				errorInfo = "WRONG_INDEX_OF_CHOSEN_ROW";
				return 0;
			}
		}
		for (KInRow kInRow : kInRowsIndexes)
		{
			RemoveKinRow(&kInRow);
		}
	}
	else
	{
		RemoveKinRow(this->kInRowsconflictingRows[rowToRemove]);
		removedConflictingRowsCount++;
	}
	this->kInRowsIndexes.clear();
	//delete this->kInRowsconflictingRows[0];
	//delete this->kInRowsconflictingRows[1];
	//delete this->kInRowsconflictingRows[2];
	//this->kInRowsconflictingRows[0] = NULL;
	//this->kInRowsconflictingRows[1] = NULL;
	//this->kInRowsconflictingRows[2] = NULL;
	CheckForGameOver();
	return removedConflictingRowsCount;
}

string GIPFEngine::CheckPawnsNumber()
{
	int countedGWFields = 0;
	int countedGBFields = 0;
	int countedStartFields = 0;
	int countedEmptyFields = 0;
	int countedForbiddenFields = 0;

	for (int i = 0; i < diag; i++)
	{
		for (int j = 0; j < diag; j++)
		{
			switch (board[i][j])
			{
			case firstPlayerField:
				countedGWFields++;
				break;
			case secondPlayerField:
				countedGBFields++;
				break;
			case startField:
				countedStartFields++;
				break;
			case emptyField:
				countedEmptyFields++;
				break;
			case forbiddenField:
				countedForbiddenFields++;
				break;
			default:
				break;
			}
		}
	}
	if (countedGWFields + gw_res > gw)
	{
		board.clear();
		return "WRONG_WHITE_PAWNS_NUMBER";
	}
	if (countedGBFields + gb_res > gb)
	{
		board.clear();
		return "WRONG_BLACK_PAWNS_NUMBER";
	}
	if (countedStartFields != s * 6)
	{
		board.clear();
		return "WRONG_START_PAWNS_NUMBER";
	}
	return "BOARD_STATE_OK";
}

int GIPFEngine::AddAllMoves(Coord dest)
{
	for (int dir = 1; dir < N + 1; dir++)
	{
		Coord sour = SpecifyNextFieldCoord(dest, static_cast<Direction>(dir));
		Coord next = SpecifyNextFieldCoord(dest, GetOppositeDirection( static_cast<Direction>(dir)));

		if (this->board[sour.first][sour.second] == startField)
		{
			if (this->board[next.first][next.second] != startField)
			{
				allMoves.push_back(pair<Coord, Coord>(sour, dest));
			}
		}
	}
	return allMoves.size();
}

void GIPFEngine::CheckForGameOver()
{
	if (emptyFieldsLeft == 0)
	{
		gameOver = true;
		winner = activePlayer + 1;
		return;
	}
	if (gw_res == 0 && activePlayer == Player::first ||
		gb_res == 0 && activePlayer == Player::second)
	{
		gameOver = true;
		winner = activePlayer + 1;
		return;
	}
	switch (activePlayer)
	{
	case Player::first:
		if (this->gb_res == 0)
		{
			gameOver = true;
			winner = Player::first;
		}
		return;
	case Player::second:
		if (this->gw_res == 0)
		{
			gameOver = true;
			winner = Player::second;
		}
		return;
	}
	return;
}

void GIPFEngine::ComputeAllMoves()
{
	int allMovesSize = 6 * (2 * (s - 2) + 3);
	if (allMoves.size() == allMovesSize) return;
	allMoves.clear();
	allMoves.resize(0);
	for (Coord i = Coord(1, 1); i.second < s; i = SpecifyNextFieldCoord(i, E))
	{
		AddAllMoves(i);
	}
	for (Coord i = Coord(1, s); i.second < diag - 2; i = SpecifyNextFieldCoord(i, SE))
	{
		AddAllMoves(i);
	}
	for (Coord i = Coord(s, diag - 2); i.first < diag - 2; i = SpecifyNextFieldCoord(i, S))
	{
		AddAllMoves(i);
	}
	for (Coord i = Coord(diag - 2, diag - 2); i.second > s; i = SpecifyNextFieldCoord(i, W))
	{
		AddAllMoves(i);
	}
	for (Coord i = Coord(diag - 2, s); i.second > 1; i = SpecifyNextFieldCoord(i, NW))
	{
		AddAllMoves(i);
	}
	for (Coord i = Coord(s, 1); i.first > 1; i = SpecifyNextFieldCoord(i, N))
	{
		AddAllMoves(i);
	}

}