#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "NMKEngine.h"
#include "Player.h"

#define UNIT_TEST

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gameEngines;

namespace UnitTestGameEngines
{

	TEST_CLASS(UnitTestNMKEngine)
	{
	public:

		// private members should not be tested !!!
		
		//TEST_METHOD(TestNewBoardShouldBeeFilledByZeros)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//  NMKEngine::K = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	Assert::AreEqual(eng->board[0][0], (char)0);
		//	Assert::AreEqual(eng->board[0][1], (char)0);
		//	Assert::AreEqual(eng->board[1][0], (char)0);
		//	Assert::AreEqual(eng->board[1][1], (char)0);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardFilledBySomeValuesShouldReturnTheSame)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//  NMKEngine::K = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	eng->board[0][0] = 1;
		//	eng->board[0][1] = 2;
		//	eng->board[1][0] = 3;
		//	eng->board[1][1] = 4;
		//	Assert::AreEqual(eng->board[0][0], (char)1);
		//	Assert::AreEqual(eng->board[0][1], (char)2);
		//	Assert::AreEqual(eng->board[1][0], (char)3);
		//	Assert::AreEqual(eng->board[1][1], (char)4);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardActivePlayerShouldBe0)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//  NMKEngine::K = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	Assert::AreEqual((int)eng->activePlayer, (int)Player::first);
		//	delete eng;
		//};

		//TEST_METHOD(TestAfterOneMoveBoardActivePlayerShouldBe1)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//  NMKEngine::K = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	NMKEngine* allPossibleMoves = (NMKEngine*)eng->GeneratePossibleMoves();
		//	Assert::AreEqual((int)allPossibleMoves[0].activePlayer, (int)Player::second);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardemptyFieldsCountField)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//  NMKEngine::K = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	Assert::AreEqual(eng->emptyFieldsCount, 9);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardIsFilledWithZeros)
		//{
		//	NMKEngine::N = 2;
		//	NMKEngine::M = 2;
		//	NMKEngine* eng = new NMKEngine();
		//	for (int i = 0; i < NMKEngine::N; i++)
		//	{
		//		for (int j = 0; j < NMKEngine::M; j++)
		//		{
		//			Assert::AreEqual(eng->board[i][j], (char)0);
		//		}
		//	}
		//	delete eng;
		//};

		TEST_METHOD(TestIsGameOverMethodOfNewNMKEngineShouldReturnFalse)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			bool res = eng->IsGameOver();
			Assert::IsFalse(res);
			delete eng;
		};

		TEST_METHOD(TestGeneratePossibleMovesMethodOfNewNMKEngineShouldReturnNotNull)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			GameEngine* res = eng->GeneratePossibleMoves(cnt, Player::first);
			Assert::IsNotNull(res);
			delete eng;
		};

		TEST_METHOD(TestNewNMKEngineShouldReturnProperState)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			Assert::AreEqual(std::string("0 0\n0 0\n"), eng->GetGameState());
			delete eng;
		};

		TEST_METHOD(TestGeneratePossibleMovesMethodOfSomeEngineAfterOneMoveShouldReturnProperState)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			Assert::AreEqual(std::string("1 0\n0 0\n"), res[0].GetGameState());
			Assert::AreEqual(std::string("0 1\n0 0\n"), res[1].GetGameState());
			Assert::AreEqual(std::string("0 0\n1 0\n"), res[2].GetGameState());
			Assert::AreEqual(std::string("0 0\n0 1\n"), res[3].GetGameState());
			delete eng;
		};

		TEST_METHOD(TestGeneratePossibleMovesMethodOfSomeEngineAfterSecondMoveShouldReturnProperState)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[2].GeneratePossibleMoves(cnt, Player::second);
			Assert::AreEqual(std::string("2 0\n1 0\n"), res[0].GetGameState());
			Assert::AreEqual(std::string("0 2\n1 0\n"), res[1].GetGameState());
			Assert::AreEqual(std::string("0 0\n1 2\n"), res[2].GetGameState());
			delete eng;
		};

		TEST_METHOD(TestGeneratePossibleMovesMethodOfSomeEngineAfterThirdMoveShouldReturnProperState)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[2].GeneratePossibleMoves(cnt, Player::second);
			res = (NMKEngine*)res[1].GeneratePossibleMoves(cnt, Player::first);
			Assert::AreEqual(std::string("1 2\n1 0\n"), res[0].GetGameState());
			Assert::AreEqual(std::string("0 2\n1 1\n"), res[1].GetGameState());
			delete eng;
		};
		TEST_METHOD(TestGeneratePossibleMovesMethodOfSomeEngineAfterFourthMoveShouldReturnProperState)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[2].GeneratePossibleMoves(cnt, Player::second);
			res = (NMKEngine*)res[1].GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[0].GeneratePossibleMoves(cnt, Player::second);
			Assert::IsNull(res);
			delete eng;
		};

		TEST_METHOD(TestIsGameOverMethodOfSomeEngineAfterFourthMoveShouldReturnTrue)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine::K = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[2].GeneratePossibleMoves(cnt, Player::second);
			res = (NMKEngine*)res[1].GeneratePossibleMoves(cnt, Player::first);
			Assert::IsTrue((NMKEngine*)res[0].IsGameOver());
			Assert::IsTrue((NMKEngine*)res[1].IsGameOver());
			delete eng;
		};

		TEST_METHOD(Test_MethodOfSomeEngineAfterFourthMoveShouldReturnTrue)
		{
			NMKEngine::N = 2;
			NMKEngine::M = 2;
			NMKEngine* eng = new NMKEngine();
			int cnt;
			NMKEngine* res = (NMKEngine*)eng->GeneratePossibleMoves(cnt, Player::first);
			res = (NMKEngine*)res[2].GeneratePossibleMoves(cnt, Player::second);
			res = (NMKEngine*)res[1].GeneratePossibleMoves(cnt, Player::first);
			Assert::AreEqual(1, res[0].Evaluate(Player::second));
			delete eng;
		};

		//TEST_METHOD(TestSolveMethod3_3_3_NMK_SetGameState_Should_Throw_Exception)
		//{
		//	//111
		//	//222
		//	//000
		//	Assert::ExpectException<std::exception>([]() {
		//		NMKEngine::N = 3;
		//		NMKEngine::M = 3;
		//		NMKEngine::K = 3;
		//		NMKEngine::ShowNodes = true;
		//		NMKEngine nmkEng;
		//		nmkEng.SetGameState("1 1 1 2 2 2 0 0 0");
		//		});
		//};
	};
}