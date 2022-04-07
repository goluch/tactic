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

		TEST_METHOD(TestSolveMethod_1_1)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine nmkEng;
			MinMaxAlg<NMKEngine> mmAlg;
			Assert::IsTrue(mmAlg.Solve(nmkEng));
		}

		//TEST_METHOD(TestSolveMethod_1_2)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 1;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine(), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_2_1)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine(), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_2_2)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine(), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_2_3)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine("1000", "0100"), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_2_4)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine("1000", "0100"), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_2_5)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine("0100", "1000"), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_2_6)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine("0100", "1000"), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_2_7)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine("0001", "0010"), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_2_8)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine("0001", "0010"), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_2_9)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsTrue(pns.Solve(CaptureGoEngine("0010", "0001"), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_2_10)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 2;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine("0001", "0010"), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_3_1)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 3;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine(), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_3_2)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 3;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine(), true, false));
		//}

		//TEST_METHOD(TestSolveMethod_4_1)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 4;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine(), true, true));
		//}

		//TEST_METHOD(TestSolveMethod_4_2)
		//{
		//	ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>> pns;
		//	CaptureGoEngine::boardSize = 4;
		//	CaptureGoEngine::initialize();
		//	Assert::IsFalse(pns.Solve(CaptureGoEngine(), true, false));
		//}

	};
}