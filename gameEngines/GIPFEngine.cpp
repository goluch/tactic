#include "GIPFEngine.h"

using namespace gameEngines;

const char GIPFEngine::firstPlayerField = 'W';
const char GIPFEngine::secondPlayerField = 'B';
const char GIPFEngine::startField = '+';
const char GIPFEngine::emptyField = '_';
const char GIPFEngine::forbiddenField = '!';

GIPFEngine::GIPFEngine(int s, int k, int gw, int gb)
{
	this->s = s;
	this->k = k;
	this->gw = gw;
	this->gb = gb;
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
	return NULL;
}

void GIPFEngine::SetGameState(string newGameState)
{
	std::stringstream ss(newGameState);

	this->winner = Player::undefined;
	{
		int x;
		ss >> x;
		if (x != s)
		{
			throw WrongGameStateSettingsException();
		};
		ss >> x;
		if (x != k)
		{
			throw WrongGameStateSettingsException();
		};
		ss >> x;
		if (x != gw)
		{
			throw WrongGameStateSettingsException();
		};
		ss >> x;
		if (x != gb)
		{
			throw WrongGameStateSettingsException();
		};
		ss >> gw_res;
		if (gw_res > gw)
		{
			throw WrongGameStateSettingsException();
		};
		ss >> gb_res;
		if (gb_res > gb)
		{
			throw WrongGameStateSettingsException();
		};
	}
	{
		char x;
		ss >> x;
		switch (x)
		{
			//zawsze zaczyna bia³y
		case firstPlayerField:
			activePlayer = Player::first;
			break;
		case secondPlayerField:
			activePlayer = Player::second;
			break;
		default:
			throw WrongGameStateSettingsException();
		}
	}
	diag = s * 2 - 1 + border * 2;
	this->board.resize(diag, vector<char>(diag));
	for (int i = 0; i < diag; i++)
	{
		for (int j = 0; j < diag; j++)
		{
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
			ss >> value;
			board[i][j] = value;
		}
	}
}

int GIPFEngine::CheckPawnsNumber()
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
	const int OK = 0;
	const int whitepawnsbadNumber = 1;
	const int blackapawnsbadNumber = 2;
	const int startFieldsbadNumber = 4;
	if (countedGWFields + gw_res != gw) return whitepawnsbadNumber;
	if (countedGBFields + gb_res != gb) return blackapawnsbadNumber;
	if (countedStartFields != s * 6) return startFieldsbadNumber;
	//if (countedEmptyFields != ???) return false;
	//if (countedForbiddenFields != ? ? ? ) return false;
	return OK;
}