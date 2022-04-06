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

		TEST_METHOD(TestBoard)
		{
			NMKEngine::N = 3;
			NMKEngine::M = 3;
			NMKEngine* eng = new NMKEngine();
			eng->board[2][2] = 1;
			Assert::AreEqual(eng->board[2][2], (char)1);
			delete eng;
		}
	};
}