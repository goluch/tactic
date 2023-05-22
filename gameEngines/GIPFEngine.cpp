#include <utility>
#include "GIPFEngine.h"
#include "GameEngineExceptions.h"

using namespace gameEngines;

const char GIPFEngine::firstPlayerField = 'W';
const char GIPFEngine::secondPlayerField = 'B';
const char GIPFEngine::startField = '+';
const char GIPFEngine::emptyField = '_';
const char GIPFEngine::forbiddenField = '!';

GIPFEngine::GIPFEngine()
{ }

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

GIPFEngine::Coord GIPFEngine::ConvertCoordinates(string Coordinates)
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

GIPFEngine::Direction GIPFEngine::SpecifyDirection(Coord sour, Coord dest)
{
	if (sour.second == dest.second)
	{
		if (sour.first == dest.first - 1)
		{
			return N;
		}
		if (sour.first == dest.first + 1)
		{
			return S;
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
	if (sour.first == dest.first - 1 && sour.first == dest.first - 1)
	{
		return SE;
	}
	if (sour.first == dest.first + 1 && sour.first == dest.first + 1)
	{
		return NW;
	}
	return Unknown;
}

GIPFEngine::Direction GIPFEngine::GetOppositeDirection(Direction moveDir)
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

GIPFEngine::Coord GIPFEngine::SpecifyNextFieldCoord(Coord sour, Direction moveDir)
{
	switch (moveDir)
	{
	case E:
		sour.second++;
		return sour;
	case S:
		sour.first--;
		return sour;
	case SE:
		sour.first++;
		sour.second++;
		return sour;
	case W:
		sour.second--;
		return sour;
	case N:
		sour.first++;
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
	//switch (moveDir)
	//{
	//case E:
	//	break;
	//case S:
	//	break;
	//case SE:
	//	break;
	//case W:
	//	break;
	//case N:
	//	break;
	//case NW:
	//	break;
	//}
	return false;
}

string GIPFEngine::DoMove(string move)
{
	Coord sour = ConvertCoordinates(move.substr(0, 2));
	if (this->board[sour.first][sour.second] != '+')
	{
		return "BAD_MOVE_" + move.substr(0, 2) + "_IS_WRONG_STARTING_FIELD";
	}
	Coord dest = ConvertCoordinates(move.substr(3));
	Direction moveDir = SpecifyDirection(sour, dest);
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
	this->activePlayer++;
	return "MOVE_COMMITTED";
}

string GIPFEngine::SetGameState(istream& newGameState)
{
	board.clear();
	this->winner = Player::undefined;
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
	if (countedGWFields + gw_res != gw) return "WRONG_WHITE_PAWNS_NUMBER";
	if (countedGBFields + gb_res != gb) return "WRONG_BLACK_PAWNS_NUMBER";
	if (countedStartFields != s * 6) return "WRONG_START_PAWNS_NUMBER";;
	//if (countedEmptyFields != ???) return false;
	//if (countedForbiddenFields != ? ? ? ) return false;
	return "BOARD_STATE_OK";
}