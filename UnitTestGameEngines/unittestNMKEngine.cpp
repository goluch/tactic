#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "NMKEngine.h"

#define UNIT_TEST

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gameEngines;

namespace UnitTestGameEngines
{
	TEST_CLASS(UnitTestGameEngines)
	{
	public:

		TEST_METHOD(TestNewBoard)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			eng->board[2][2] = 1;
			Assert::AreEqual(eng->board[2][2], (char)1);
			delete eng;
		}

		TEST_METHOD(TestNewBoardActivePlayerShouldBe0)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			Assert::AreEqual(eng->activePlayer, 0);
			delete eng;
		}

		TEST_METHOD(TestAfterOneMoveBoardActivePlayerShouldBe1)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			eng->GeneratePossibleMoves();
			Assert::AreEqual(eng->activePlayer, 1);
			delete eng;
		}

		TEST_METHOD(TestNewBoardemptyFieldsCountField)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();			 
			Assert::AreEqual(eng->emptyFieldsCount, 9);
			delete eng;
		}

		TEST_METHOD(TestNewBoardIsFilledWithZeros)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			for (int i = 0; i < NMKEngine::N; i++)
			{
				for (int j = 0; j < NMKEngine::M; j++)
				{
					Assert::AreEqual(eng->board[i][j], (char)0);
				}
			}
			delete eng;
		}

		TEST_METHOD(TestisGameOverMethodShouldReturnFalse)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			bool res = eng->isGameOver();
			Assert::IsFalse(res);
			delete eng;
		}

		TEST_METHOD(TestGeneratePossibleMovesMethodShouldReturnFalse)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			GameEngine* res = eng->GeneratePossibleMoves();
			Assert::IsNotNull(res);
			delete eng;
		}
	};
}