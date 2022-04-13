#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "Minmax.h"
//#include "exceptions.h"
#include "NMKEngine.h"
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
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod3_2_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod2_3_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 3;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod3_3_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod4_2_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 4;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod2_4_2_NMK_firstPlayerWins)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 4;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		TEST_METHOD(TestSolveMethod3_3_3_NMK_firstPlayerWins)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine::K = 3;
			NMKEngine nmkEng;
			MinmaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

	};
}