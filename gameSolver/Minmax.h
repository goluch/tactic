#ifndef MINMAXALG
#define MINMAXALG

#pragma once
#include "GameEngine.h"
#include "PerformanceCounter.h"
#include "limits.h"

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

        int Minmax(G& gameState, Player activePlayer)
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
            G* allPossibleMoves = NULL;
            int movesCount = gameState.GeneratePossibleMoves(allPossibleMoves, activePlayer);
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
                Player nextPlayer = activePlayer + 1;
                for (int i = 0; i < movesCount; i++)
                {
                    best = max(best, Minmax(allPossibleMoves[i], nextPlayer));
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
                Player nextPlayer = activePlayer + 1;
                for (int i = 0; i < movesCount; i++)
                {
                    best = min(best, Minmax(allPossibleMoves[i], nextPlayer));
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