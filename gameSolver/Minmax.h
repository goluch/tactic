#ifndef MINMAXALG
#define MINMAXALG

//#define PRINTING

#pragma once
#include "utils.h"
#include "GameEngine.h"
#include "PerformanceCounter.h"
#include <limits.h>

namespace gameSolver
{
    template<typename G>
    class MinmaxAlg
    {
        
    public:

        bool cutIfPossible;

        MinmaxAlg()
        {

        }

        ~MinmaxAlg()
        {

        }

        int Solve(G gameState, Player activePlayer, PerformanceCounter* pc = nullptr)
        {

#ifdef _DEBUG
            if (pc)
            {
                //liczymy performance
            }
#endif
            return Minmax(gameState, activePlayer);
        };

    protected:
        //void StartExecutionTimeMeasurement();
        //void StopExecutionTimeMeasurement();

    private:

        int Minmax(G gameState, Player activePlayer)
        {
            int score = gameState.Evaluate(activePlayer);

#ifdef PRINTING
            cout << gameState.GetGameState() << "Result: " << score << endl;
#endif //PRINTING

            if (score >= -1 && score <= 1)
            {
                return score;
            }
            int movesCount;
            G* allPossibleMoves = (G*)gameState.GeneratePossibleMoves(movesCount, activePlayer);
#ifdef PRINTING
            for (int i = 0; i < movesCount; i++)
            {
                if (i) { cout << "------" << endl; }
                cout << allPossibleMoves[i].GetGameState();
            }
            cout << "******" << endl;
#endif //PRINTING
            if (activePlayer == Player::first)
            {
                int best = INT_MIN;
                for (int i = 0; i < movesCount; i++)
                {
                    best = maximum(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                    if (cutIfPossible && best == 1)
                    {
                        break;
                    }
                }
                delete[] allPossibleMoves;
                return best;
            }
            else
            {
                int best = INT_MAX;
                for (int i = 0; i < movesCount; i++)
                {
                    best = minimum(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                    if (cutIfPossible && best == -1)
                    {
                        break;
                    }
                }
                delete[] allPossibleMoves;
                return best;
            }
        }
    };

}

#endif