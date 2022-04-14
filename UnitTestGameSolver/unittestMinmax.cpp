#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "Minmax.h"
//#include "exceptions.h"
#include "NMKEngine.h"
#include "utils.h"

using namespace gameEngines;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gameSolver;

namespace UnitTestGameSolver
{
	TEST_CLASS(UnitTestMinmax)
	{
	public:

		TEST_METHOD(TestSolveMethod2_2_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_2_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod2_3_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 3;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_3_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod4_2_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 4;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod2_4_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 4;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_firstPlayerDraws)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(0, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_4_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 4;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod4_4_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 4;
			NMKEngine::M = 4;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			nmkEng.SetGameState("0 0 0 1 2 0 2 0 0 0 1 0 0 0 0 0");
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_4_3_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 4;
			NMKEngine::K = 3;
			NMKEngine nmkEng;
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod4_4_3_NMK_firstPlayerWins)
		{
			NMKEngine::N = 4;
			NMKEngine::M = 4;
			NMKEngine::K = 3;
			NMKEngine nmkEng;
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod4_4_4_NMK_firstPlayerWins)
		{
			NMKEngine::N = 4;
			NMKEngine::M = 4;
			NMKEngine::K = 4;
			NMKEngine nmkEng;
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_secondPlayerWins_TwoFreePlaces)
		{
			//212
			//121
			//100
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine::ShowNodes = true;
			NMKEngine nmkEng;
			nmkEng.SetGameState("2 1 2 1 2 1 1 0 0");
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(-1, mmAlg.Solve(nmkEng, Player::second));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_firstPlayerDraws_OneFreePlaces)
		{
			//212
			//121
			//120
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine::ShowNodes = true;
			NMKEngine nmkEng;
			nmkEng.SetGameState("2 1 2 1 2 1 1 2 0");
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(0, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_secondPlayerWins_OneFreePlaces_GameIsOver_1)
		{
			//212
			//121
			//102
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine::ShowNodes = true;
			NMKEngine nmkEng;
			nmkEng.SetGameState("2 1 2 1 2 1 1 0 2");
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(-1, mmAlg.Solve(nmkEng, Player::first));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_secondPlayerWins_OneFreePlaces_GameIsOver_2)
		{
			//111
			//220
			//000
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine::ShowNodes = true;
			NMKEngine nmkEng;
			nmkEng.SetGameState("1 1 1 2 2 0 0 0 0");
			gameSolver::MinmaxAlg<NMKEngine> mmAlg;
			Assert::AreEqual(1, mmAlg.Solve(nmkEng, Player::second));
		}
	};
}