#pragma once
#include <vector>
#include "Player.h"
#include "GameEngine.h"
#include "GameEngineExceptions.h"
namespace gameEngines
{
    template<int S, int K, int GW, int GB>
    class GIPFEngine
        : public GameEngine
    {
    public:

		//border is the outer fields of the board intended for pieces added at the beginning of the move
		static int border;
		static int diag;
        static string info;
		static const char firstPlayerField;
		static const char secondPlayerField;
		static const char startField;
		static const char emptyField;
		static const char forbiddenField;

        GIPFEngine()
        { }

        ~GIPFEngine()
        { }

        virtual int Evaluate(Player)
		{
			return 0;
		}
        virtual GameEngine* GeneratePossibleMoves(int& count, Player activePlayer)
		{
			return NULL;
		}
        virtual string GetGameState()
		{
			return NULL;
		}
		virtual void SetGameState(string newGameState)
		{
			std::stringstream ss(newGameState);

			this->winner = Player::undefined;
			{
				int x;
				ss >> x;
				if (x != S)\
				{
					throw WrongGameStateSettingsException();
				};
				ss >> x;
				if (x != K)\
				{
					throw WrongGameStateSettingsException();
				};
				ss >> x;
				if (x != GW)\
				{
					throw WrongGameStateSettingsException();
				};
				ss >> x;
				if (x != GB)\
				{
					throw WrongGameStateSettingsException();
				};
				ss >> gw;
				if (gw > GW)\
				{
					throw WrongGameStateSettingsException();
				};
				ss >> gb;
				if (gb > GB)\
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
			this->board.resize(diag, vector<char>(diag));
			for (int i = 0; i < diag; i++)
			{
				for (int j = 0; j < diag; j++)
				{
					if (j > S + i || i > S + j)
					{
						board[i][j] = forbiddenField;
						continue;
					}
					if (i == 0 || j == 0 || i == diag - 1 || j == diag - 1 || j == S + i || i == S + j)
					{
						board[i][j] = startField;
						continue;
					}
					ss >> value;
					board[i][j] = value;
				}
			}
        }

		int CheckPawnsNumber()
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
			if (countedGWFields + gw != GW) return whitepawnsbadNumber;
			if (countedGBFields + gb != GB) return blackapawnsbadNumber;
			if (countedStartFields != S * 6) return startFieldsbadNumber;
			//if (countedEmptyFields != ???) return false;
			//if (countedForbiddenFields != ? ? ? ) return false;
			return OK;
		}

    private:

		int gw;
		int gb;
		char value;
		Player activePlayer;
		vector<vector<char>> board;

    };

	template<int S, int K, int GW, int GB>
	int GIPFEngine<S, K, GW, GB>::border = 1;

	template<int S, int K, int GW, int GB>
	int GIPFEngine<S, K, GW, GB>::diag = S * 2 - 1 + border * 2;

	//always starts white
	template<int S, int K, int GW, int GB>
	char const GIPFEngine<S, K, GW, GB>::firstPlayerField = 'W';

	template<int S, int K, int GW, int GB>
	char const GIPFEngine<S, K, GW, GB>::secondPlayerField = 'B';

	template<int S, int K, int GW, int GB>
	char const GIPFEngine<S, K, GW, GB>::startField = '+';

	template<int S, int K, int GW, int GB>
	char const GIPFEngine<S, K, GW, GB>::emptyField = '_';

	template<int S, int K, int GW, int GB>
	char const GIPFEngine<S, K, GW, GB>::forbiddenField = '!';

}