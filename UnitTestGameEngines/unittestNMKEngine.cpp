#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "NMKEngine.h"
#include <Player.h>

#define UNIT_TEST

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gameEngines;

namespace UnitTestGameEngines
{


	TEST_CLASS(UnitTestGameEngines)
	{
	public:

		TEST_METHOD(TestNewPlayerShouldBeFirst)
		{
			Player player = Player::first;
			Assert::AreEqual((int)player, (int)Player::first);
		};

		TEST_METHOD(TestIncrementedFirstPlayerShouldBeSecond)
		{
			Player player = Player::first;
			player++;
			Assert::AreEqual((int)player, (int)Player::second);
		};

		TEST_METHOD(TestIncrementedTwiceFirstPlayerShouldBeFirst)
		{
			Player player = Player::first;
			player++;
			player++;
			Assert::AreEqual((int)player, (int)Player::first);
		};

		TEST_METHOD(TestIncrementedThreeTimesFirstPlayerShouldBeSecond)
		{
			Player player = Player::first;
			player++;
			player++;
			player++;
			Assert::AreEqual((int)player, (int)Player::second);
		};

		//TEST_METHOD(TestNewBoard)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	eng->board[2][2] = 1;
		//	Assert::AreEqual(eng->board[2][2], (char)1);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardActivePlayerShouldBe0)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	Assert::AreEqual((int)eng->activePlayer, (int)Player::first);
		//	delete eng;
		//};

		//TEST_METHOD(TestAfterOneMoveBoardActivePlayerShouldBe1)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	eng->GeneratePossibleMoves();
		//	Assert::AreEqual((int)eng->activePlayer, (int)Player::second);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardemptyFieldsCountField)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	Assert::AreEqual(eng->emptyFieldsCount, 9);
		//	delete eng;
		//};

		//TEST_METHOD(TestNewBoardIsFilledWithZeros)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
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

		//TEST_METHOD(TestisGameOverMethodShouldReturnFalse)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	bool res = eng->IsGameOver();
		//	Assert::IsFalse(res);
		//	delete eng;
		//};

		//TEST_METHOD(TestGeneratePossibleMovesMethodShouldReturnFalse)
		//{
		//	NMKEngine::N = 3;
		//	NMKEngine::M = 3;
		//	NMKEngine* eng = new NMKEngine();
		//	GameEngine* res = eng->GeneratePossibleMoves();
		//	Assert::IsNotNull(res);
		//	delete eng;
		//};
	};
}