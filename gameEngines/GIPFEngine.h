#pragma once
#include "Player.h"
#include "GameEngine.h"
namespace gameEngines
{
    template<int S, int K, int GW, int GB>
    class GIPFEngine
        : public GameEngine
    {
    public:

        static int border;
        static string Info;

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
		virtual void SetGameState(string gameState)
		{
			return;
		}
			/*{
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

					if (!value)
					{
						this->emptyFieldsCount++;
					}
				}
			}
			for (int i = 1; i < N + border; i++)
			{
				for (int j = 1; j < M + border; j++)
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
        }*/

    private:

    };

}