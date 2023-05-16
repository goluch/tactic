#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "GIPFEngine.h"
#include "Player.h"

#define UNIT_TEST

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gameEngines;

namespace UnitTestGameEngines
{

	TEST_CLASS(UnitTestGIPFEngine)
	{
	public:

		TEST_METHOD(TestIsGameOverMethodOfNewNMKEngineShouldReturnFalse)
		{
			const int s = 4; //board size
			const int k = 4; //k-in-row
			const int gw = 4; //white pawns number
			const int gb = 4; //black pawns number
			GameEngine* eng = new GIPFEngine<s, k, gw, gb>();
			bool res = eng->IsGameOver();
			Assert::IsFalse(res);
			delete eng;
		};

	};
}