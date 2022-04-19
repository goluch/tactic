#ifndef MINMAXALG
#define MINMAXALG

#pragma once
#include "GameEngine.h"
#include "PerformanceCounter.h"
#include <limits.h>

namespace gameSolver
{
    static bool cutIfGameOver;

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

        int Solve(G gameState, Player activePlayer, bool cut = false, PerformanceCounter* pc = nullptr)
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

            if (cutIfGameOver && score >= -1 && score <= 1)
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
                    best = max(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                    if (best == 1)
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
                    best = min(best, Minmax(allPossibleMoves[i], activePlayer + 1));
                    if (best == -1)
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