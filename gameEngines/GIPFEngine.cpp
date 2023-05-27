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

GIPFEngine::GIPFEngine()
{
	ClearGameState();
}

GIPFEngine::~GIPFEngine()
{ }

int GIPFEngine::Evaluate(Player)
{
	return 0;
}

GameEngine* GIPFEngine::GeneratePossibleMoves(int& count, Player activePlayer)
{
	return NULL;
}

string GIPFEngine::GetGameState()
{
	stringstream ss;
	ss << this->s << " " << this->k << " " << this->gw << " " << this->gb << endl;
	ss << this->gw_res << " " << this->gb_res << " " << (activePlayer == Player::first ? 'W' : 'B') << endl;
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
			case 'W':
				ss << 'W';
				break;
			case 'B':
				ss << 'B';
				break;
			case '_':
				ss << '_';
				break;
			case '+':
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
		if (board[prev.first][prev.second] == '+')
		{
			board[dest.first][dest.second] = activePlayer == Player::first ? 'W' : 'B';
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
	Direction moveDir = SpecifyDirection(sour, dest);
	if (moveDir == Unknown)
	{
		return "UNKNOWN_MOVE_DIRECTION";
	}
	while (this->board[dest.first][dest.second] != '_')
	{
		switch (this->board[dest.first][dest.second])
		{
		case 'W':
			dest = SpecifyNextFieldCoord(dest, moveDir);
			break;
		case 'B':
			dest = SpecifyNextFieldCoord(dest, moveDir);
			break;
		case '+':
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
	string removedInfo;
	int removedRows = RemoveKInRows(removedInfo);
	if (removedInfo != "")
	{
		return removedInfo;
	}
	this->activePlayer++;
	return "MOVE_COMMITTED";
}

void GIPFEngine::ClearGameState()
{
	board.clear();
	this->kInRowsconflictingRows[0] = NULL;
	this->kInRowsconflictingRows[1] = NULL;
	this->kInRowsconflictingRows[2] = NULL;
	this->collisionInKInRowsNumber = 0;
	this->winner = Player::undefined;
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
		//zawsze zaczyna bia³y
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
			board[i][j] = value;
		}
	}
	if (value != '\n')
	{
		board.clear();
		return "WRONG_BOARD_ROW_LENGTH";
	}
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
	case 'W':
	case 'B':
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
			this->collisionInKInRowsNumber++;
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
	//if (foundKInRows != this->kInRowsIndexes.size() + this->collisionInKInRowsNumber * 2)
	//{
	//	throw WrongGameStateSettingsException("Wrong kInRowsIndexes size");
	//}
	return foundKInRows;
}

bool GIPFEngine::UpdatePlayersReserves(Coord tmpCoord, char kInRowColor)
{
	char fieldColor = this->board[tmpCoord.first][tmpCoord.second];
	if (fieldColor == 'W' || fieldColor == 'B')
	{
		this->board[tmpCoord.first][tmpCoord.second] = '_';
		switch (kInRowColor)
		{
		case 'W':
			if (fieldColor == 'W')
			{
				gw_res++;
			}
			return true;
		case 'B':
			if (fieldColor == 'B')
			{
				gb_res++;
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

int GIPFEngine::RemoveKInRows(string& errorInfo)
{
	// raczej istnienie wiêcej ni¿ jednej kolizjii nie jest mo¿liwe podczas normalnej gry wiêc mo¿na z czasem zamieniæ na bool.
	int removedConflictingRowsCount = 0;
	while (this->collisionInKInRowsNumber--)
	{
		string removingPlayerColor;
		cin >> removingPlayerColor;
		switch (board[this->collisionIndex.first][this->collisionIndex.second])
		{
		case 'W':
			if (removingPlayerColor.compare("b:") == 0)
			{
				errorInfo = "WRONG_COLOR_OF_CHOSEN_ROW";
				return 0;
			}
			break;
		case 'B':
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

		if (this->kInRowsconflictingRows[0] !=  NULL)
			if(this->kInRowsconflictingRows[0]->row.front() == RowBeginIndex &&
			this->kInRowsconflictingRows[0]->row.back() == RowEndIndex ||
			this->kInRowsconflictingRows[0]->row.front() == RowEndIndex &&
			this->kInRowsconflictingRows[0]->row.back() == RowBeginIndex)
		{
			RemoveKinRow(this->kInRowsconflictingRows[0]);
			removedConflictingRowsCount++;
		}
		if (this->kInRowsconflictingRows[1] != NULL)
			if(this->kInRowsconflictingRows[1]->row.front() == RowBeginIndex &&
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
	int removed = removedConflictingRowsCount;
	for (KInRow kInRow : kInRowsIndexes)
	{
		RemoveKinRow(&kInRow);
	}
	this->kInRowsIndexes.clear();
	delete this->kInRowsconflictingRows[0];
	delete this->kInRowsconflictingRows[1];
	delete this->kInRowsconflictingRows[2];
	this->kInRowsconflictingRows[0] = NULL;
	this->kInRowsconflictingRows[1] = NULL;
	this->kInRowsconflictingRows[2] = NULL;
	return removed;
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
	if (countedGWFields + gw_res > gw) return "WRONG_WHITE_PAWNS_NUMBER";
	if (countedGBFields + gb_res > gb) return "WRONG_BLACK_PAWNS_NUMBER";
	if (countedStartFields != s * 6) return "WRONG_START_PAWNS_NUMBER";;
	//if (countedEmptyFields != ???) return false;
	//if (countedForbiddenFields != ? ? ? ) return false;
	return "BOARD_STATE_OK";
}