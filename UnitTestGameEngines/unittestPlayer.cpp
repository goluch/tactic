#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "CppUnitTest.h"
#include "NMKEngine.h"
#include "Player.h"

#define UNIT_TEST

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGameEngines
{

	TEST_CLASS(UnitTestPlayer)
	{
	public:

		TEST_METHOD(TestNewPlayerShouldBeFirst)
		{
			Player player = Player::first;
			Assert::AreEqual((int)Player::first, (int)player);
		};

		TEST_METHOD(TestIncrementedFirstPlayerShouldBeSecond)
		{
			Player player = Player::first;
			player++;
			Assert::AreEqual((int)Player::second, (int)player);
		};

		TEST_METHOD(TestIncrementedTwiceFirstPlayerShouldBeFirst)
		{
			Player player = Player::first;
			player++;
			player++;
			Assert::AreEqual((int)Player::first, (int)player);
		};

		TEST_METHOD(TestIncrementedThreeTimesFirstPlayerShouldBeSecond)
		{
			Player player = Player::first;
			player++;
			player++;
			player++;
			Assert::AreEqual((int)Player::second, (int)player);
		};
	};
}