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

		TEST_METHOD(TestIsGameOverMethodOfNewGIPFEngineShouldReturnFalse)
		{
			GIPFEngine* eng = new GIPFEngine();
			bool res = eng->IsGameOver();
			Assert::IsFalse(res);
			delete eng;
		};

		TEST_METHOD(TestGeneratePossibleMovesMethodOfNewGIPFEngineShouldReturnNotNull)
		{
			GIPFEngine* eng = new GIPFEngine();
			int cnt;
			GameEngine* res = eng->GeneratePossibleMoves(cnt, Player::first);
			Assert::IsNotNull(res);
			delete eng;
		};

		TEST_METHOD(TestSetGameStateMethod_Empty_String_Should_Throw_Exception)
		{
			GIPFEngine* eng = new GIPFEngine();
			string emptyString = "";
			Assert::ExpectException<WrongGameStateSettingsException>([&]()
				{
					eng->SetGameState(stringstream(emptyString));
				});
			delete eng;
		};

		TEST_METHOD(TestSetGameStateMethod_Proper_String_Should_Not_Throw_Exception)
		{
			GIPFEngine* eng = new GIPFEngine();
			string properString =
				"4 4 15 15\n"
				"12 12 W\n"
				"   W _ _ B\n"
				"  _ _ _ _ _\n"
				" _ _ _ _ _ _\n"
				"B _ _ _ _ _ W\n"
				" _ _ _ _ _ _\n"
				"  _ _ _ _ _\n"
				"   W _ _ B";
			eng->SetGameState(stringstream(properString));
			delete eng;
		};

		TEST_METHOD(TestCheckPawnsNumberMethod_Proper_Board_Returns_OK)
		{
			GIPFEngine* eng = new GIPFEngine();
			string properString =
				"4 4 15 15\n"
				"12 12 W\n"
				"   W _ _ B\n"
				"  _ _ _ _ _\n"
				" _ _ _ _ _ _\n"
				"B _ _ _ _ _ W\n"
				" _ _ _ _ _ _\n"
				"  _ _ _ _ _\n"
				"   W _ _ B";
			eng->SetGameState(stringstream(properString));
			Assert::AreEqual("BOARD_STATE_OK", eng->CheckPawnsNumber().c_str());
			delete eng;
		};

	};
}