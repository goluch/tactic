#pragma once
#include <time.h>
#include "GameEngine.h"
#include "PerformanceCounter.h"
#include "limits.h"
#include "utils.h"

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
            return Minmax(gameState, true) == 1 ? true : false;
        };

    protected:
        //void StartExecutionTimeMeasurement();
        //void StopExecutionTimeMeasurement();

    private:

        int Minmax(G gameState, bool isMax)
        {
            int score = gameState.Evaluate();

            if (score > -1 || score < 1)
            {
                return score;
            }
            int movesCount = gameState.GetNumberOfPossibleMoves();
            G* allPossibleMoves = (G*)gameState.GeneratePossibleMoves();
            if (isMax)
            {
                int best = INT_MAX;
                for (int i = 0; i < movesCount; i++)
                {
                    best = max(best, Minmax(allPossibleMoves[i], !isMax));
                }
                return best;
            }
            else
            {
                int best = INT_MAX;
                for (int i = 0; i < movesCount; i++)
                {
                    best = max(best, Minmax(allPossibleMoves[i], !isMax));
                }
                return best;
            }
        }
    };

}