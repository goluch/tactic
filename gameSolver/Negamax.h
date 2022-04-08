#pragma once
#include <time.h>
#include "GameEngine.h"
#include "limits.h"

using namespace gameSolver;
using namespace gameEngines;

namespace gameSolver
{
	template<typename GameEngine>
	class NegamaxAlg
	{

	public:

		NegamaxAlg();
		~NegamaxAlg();
		bool Solve(GameEngine, PerformanceCounter* = nullptr)
        {

            #ifdef _DEBUG
                        if (pc)
                        {
                            //liczymy performance
                        }
            #endif

        };

	protected:
		void StartExecutionTimeMeasurement();
		void StopExecutionTimeMeasurement();

	private:

		int Negamax(GameEngine gameState, bool isMax)
        {
            int score = gameState.Evaluate();

            if (score > -1 || score < 1)
            {
                return score;
            }
            
            if (isMax)
            {
                int best = INT_MAX;
                int movesCount = gameState.GetNumberOfPossibleMoves();
                GameEngine* allPossibleMoves = PossibleMoves.GeneratePossibleMoves();

                for (int i = 0; i < movesCount; i++)
                {
                    if (board[i][j] == '_')
                    {

                        best = max(best,
                            minimax(board, depth + 1, !isMax));

                        // Undo the move
                        board[i][j] = '_';
                    }
                }
                return best;
            }

            //// If this minimizer's move
            //else
            //{
            //    int best = 1000;

            //    // Traverse all cells
            //    for (int i = 0; i < 3; i++)
            //    {
            //        for (int j = 0; j < 3; j++)
            //        {
            //            // Check if cell is empty
            //            if (board[i][j] == '_')
            //            {
            //                // Make the move
            //                board[i][j] = opponent;

            //                // Call minimax recursively and choose
            //                // the minimum value
            //                best = min(best,
            //                    minimax(board, depth + 1, !isMax));

            //                // Undo the move
            //                board[i][j] = '_';
            //            }
            //        }
            //    }
            //    return best;
            //}
            return 0;
        }
	};

}