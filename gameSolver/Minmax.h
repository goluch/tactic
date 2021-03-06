#ifndef MINMAXALG
#define MINMAXALG

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

            //if (NMKEngine::ShowNodes)
            //{
            //    std::cout << gameState.GetGameState() << "Result: " << score << endl;
            //}

            if (score >= -1 && score <= 1)
            {
                return score;
            }
            int movesCount;
            G* allPossibleMoves = (G*)gameState.GeneratePossibleMoves(movesCount, activePlayer);
            // ************** drukowanie **************
            //if (NMKEngine::ShowNodes)
            //{
            //    for (int i = 0; i < movesCount; i++)
            //    {
            //        if (i) { cout << "------" << endl; }
            //        std::cout << allPossibleMoves[i].GetGameState();
            //    }
            //    std::cout << "******" << endl;
            //}
            // *********** koniec drukowania ***********
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