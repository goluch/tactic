#include "GIPFEngine.h"

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
	ss << this->gb_res << " " << this->gw_res << " " << (activePlayer == Player::first ? 'W' : 'B') << endl;
	for (int i = 1; i < diag - 1; i++)
	{
		int spacesPrefix = (i > s) ? s - i : s - i;
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


string GIPFEngine::SetGameState(istream& newGameState)
{
	board.clear();
	this->winner = Player::undefined;
	newGameState >> s >> k >> gw >> gb;
	newGameState >> gw_res;
	if (gw_res > gw)
	{
		//throw WrongGameStateSettingsException("WRONG_WHITE_PAWNS_NUMBER");
		board.clear();
		return "WRONG_WHITE_PAWNS_NUMBER";
	};
	newGameState >> gb_res;
	if (gb_res > gb)
	{
		//throw WrongGameStateSettingsException("WRONG_BLACK_PAWNS_NUMBER");
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
		//throw WrongGameStateSettingsException("UNKNOWN_ACTIVE_PLAYER");
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
							//throw WrongGameStateSettingsException("WRONG_BOARD_ROW_LENGTH");
							board.clear();
							return "WRONG_BOARD_ROW_LENGTH";
						}
					}
					else
					{
						if (j != diag - 1)
						{
							//throw WrongGameStateSettingsException("WRONG_BOARD_ROW_LENGTH");
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
		//throw WrongGameStateSettingsException("WRONG_BOARD_ROW_LENGTH");
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