#ifndef MINMAXALG
#define MINMAXALG

#pragma once
#include <time.h>
#include "GameEngine.h"
#include "PerformanceCounter.h"
#include "limits.h"
//#include "utils.h"

namespace gameSolver
{
    template<typename G>
    class MinmaxAlg
    {

    public:

        MinmaxAlg()
        {

        }

        ~MinmaxAlg()
        {

        }

        bool Solve(G gameState, PerformanceCounter* pc = nullptr)
        {

#ifdef _DEBUG
            if (pc)
            {
                //liczymy performance
            }
#endif
            int res = Minmax(gameState, Player::first) == 1 ? true : false;
            return res;
        };

    protected:
        //void StartExecutionTimeMeasurement();
        //void StopExecutionTimeMeasurement();

    private:

        int Minmax(G gameState, Player activePlayer)
        {
            int score = gameState.Evaluate(activePlayer);

            if (score >= -1 && score <= 1)
            {
                return score;
            }
            int movesCount = gameState.GetNumberOfPossibleMoves(activePlayer);
            G* allPossibleMoves = (G*)gameState.GeneratePossibleMoves(activePlayer);
            if (activePlayer == Player::first)
            {
                int best = INT_MIN;
                for (int i = 0; i < movesCount; i++)
                {
                    best = max(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                }
                return best;
            }
            else
            {
                int best = INT_MAX;
                for (int i = 0; i < movesCount; i++)
                {
                    best = min(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                }
                return best;
            }
        }
    };

}

#endif