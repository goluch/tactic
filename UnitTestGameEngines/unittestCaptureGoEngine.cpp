//#include <stdio.h>
//#include <tchar.h>
//#include <iostream>
//#include "CppUnitTest.h"
//#include "CaptureGoEngine.cpp"
//
//#define UNIT_TEST
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTestGameEngines
//{		
//	TEST_CLASS(UnitTestGameEngines)
//	{
//	public:
//		
//		/* Indeksy planszy 9 x 9 (mini Go) odpowiadaj¹ kolejnym bitom (od najm³odszego).
//
//		-------------------------------------
//		|  0|  1|  2|  3|  4|  5|  6|  7|  8|
//		-------------------------------------
//		|  9| 10| 11| 12| 13| 14| 15| 16| 17|
//		-------------------------------------
//		| 18| 19| 20| 21| 22| 23| 24| 25| 26|
//		-------------------------------------
//		| 27| 28| 29| 30| 31| 32| 33| 34| 35|
//		-------------------------------------
//		| 36| 37| 38| 39| 40| 41| 42| 43| 44|
//		-------------------------------------
//		| 45| 46| 47| 48| 49| 50| 51| 52| 53|
//		-------------------------------------
//		| 54| 55| 56| 57| 58| 59| 60| 61| 62|
//		-------------------------------------
//		| 63| 64| 65| 66| 67| 68| 69| 70| 71|
//		-------------------------------------
//		| 72| 73| 74| 75| 76| 77| 78| 79| 80|
//		-------------------------------------
//
//		Indeksy planszy 8 x 8 (najwiêksza na typie unsigned long long) odpowiadaj¹ kolejnym bitom (od najm³odszego).
//
//		---------------------------------
//		|  0|  1|  2|  3|  4|  5|  6|  7|
//		---------------------------------
//		|  8|  9| 10| 11| 12| 13| 14| 15|
//		---------------------------------
//		| 16| 17| 18| 19| 20| 21| 22| 23|
//		---------------------------------
//		| 24| 25| 26| 27| 28| 29| 30| 31|
//		---------------------------------
//		| 32| 33| 34| 35| 36| 37| 38| 39|
//		---------------------------------
//		| 40| 41| 42| 43| 44| 45| 46| 47|
//		---------------------------------
//		| 48| 49| 50| 51| 52| 53| 54| 55|
//		---------------------------------
//		| 56| 57| 58| 59| 60| 61| 62| 63|
//		---------------------------------
//		
//		*/
//
//		// test metody monwertuj¹cej ze stringa reprezentuj¹cego piony na planszy do liczby
//
//		TEST_METHOD(TestpawnsFromStringToLongMethod_8_1)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine();
//
//			Assert::AreEqual(eng->pawnsFromStringToLong("0000000000000000000000000000000000000000000000001000000001000000"),
//				(unsigned long long) 144396663052566528);
//		}
//
//		TEST_METHOD(TestpawnsFromStringToLongMethod_8_2)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine();
//
//			Assert::AreEqual(eng->pawnsFromStringToLong("0000000000000000000000000000000000000000000000000000000010000000"),
//				(unsigned long long) 72057594037927936);
//		}
//
//		TEST_METHOD(TestpawnsFromStringToLongMethod_8_3)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine();
//
//			Assert::AreEqual(eng->pawnsFromStringToLong("1111111111111111111111111111111111111111111111111111111111111111"),
//				(unsigned long long) 18446744073709551615);
//		}
//
//		// test metody inicjalizuj¹cej maski statyczne okreœlaj¹ce pola osi¹galne po posuniêciu o jedno pole w lewo/prawo
//
//		TEST_METHOD(TestMasksInitializeMethod_1_1)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::leftBorderMask, (unsigned long long) 0);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_1_2)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::rightBorderMask, (unsigned long long) 0);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_2_1)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::leftBorderMask, (unsigned long long) 5);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_2_2)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::rightBorderMask, (unsigned long long) 10);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_3_1)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::leftBorderMask, (unsigned long long) 219);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_3_2)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::rightBorderMask, (unsigned long long) 438);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_8_1)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::leftBorderMask, (unsigned long long) 9187201950435737471);
//		}
//
//		TEST_METHOD(TestMasksInitializeMethod_8_2)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			Assert::AreEqual(CaptureGoEngine::rightBorderMask, (unsigned long long) 18374403900871474942);
//		}
//
//		// test metody sprawdzaj¹cej zakoñczeni rozgrywki i zwracaj¹cej informacjê o wygranym graczu
//
//		TEST_METHOD(TestCaptureGoEngineMethod_1_1)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0", "0");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_1_2)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1", "0");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_1_3)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0", "1");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_1_4)
//		{
//			CaptureGoEngine::boardSize = 1;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1", "0");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsFalse(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_1)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000", "0000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_2)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1000", "0000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_3)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0100", "0000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_4)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0010", "0000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_5)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0001", "0000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_6)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0110", "1000");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_7)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0110", "0001");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_8)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1001", "0100");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_9)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1001", "0010");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//
// 		TEST_METHOD(TestCaptureGoEngineMethod_2_10)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1000", "0100");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_11)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0100", "1000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_12)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1000", "0010");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_13)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0010", "1000");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_14)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0001", "0010");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_15)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0010", "0001");
//
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_16)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1010", "0101");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_17)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1010", "0101");
//
//			bool *isWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsItAWinner(true, isWinner);
//			Assert::IsTrue(*isWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_2_18)
//		{
//			CaptureGoEngine::boardSize = 2;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1010", "0101");
//
//			bool *isWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsItAWinner(false, isWinner);
//			Assert::IsTrue(*isWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_3_1)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("001010110", "010101001");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_3_2)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("010101001", "000010110");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_3_3)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("010101001", "000010110");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_3_4)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("010010100", "100100000");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_3_5)
//		{
//			CaptureGoEngine::boardSize = 3;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("010010100", "100100000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_4_1)
//		{
//			CaptureGoEngine::boardSize = 4;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1000100101100000", "0110011010000000");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_4_2)
//		{
//			CaptureGoEngine::boardSize = 4;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("1000100101100000", "0110011010000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsFalse(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_5_1)
//		{
//			CaptureGoEngine::boardSize = 4;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000011111000001111100000", "0000000000111110000000000");
//
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_5_2)
//		{
//			CaptureGoEngine::boardSize = 4;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000011111000001111100000", "0000000000111110000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsFalse(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_7_)
//		{
//			CaptureGoEngine::boardSize = 7;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("00000001111111000000011111110000000000000000000000",
//				"00000000000000111111100000000000000000000000000000");
//		
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_7_2)
//		{
//			CaptureGoEngine::boardSize = 7;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("00000001111111000000011111110000000000000000000000",
//				"00000000000000111111100000000000000000000000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_1)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000000000000000000000000000000000000",
//				"0000000000000000000000000000000000000000000000000000000000000000");
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_2)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000001000000000000000000000000000000",
//				"0000000000000000000000000000000000000000000000000000000000000000");
//			Assert::IsFalse(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_3)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0100000010000000000000000000000000000000000000000000000000000000",
//				"1000000000000000000000000000000000000000000000000000000000000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_4)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0100000010000000000000000000000000000000000000000000000000000000",
//				"1000000000000000000000000000000000000000000000000000000000000000");
//			
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_5)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000001000000001000000000000000000000000000000000000000000000000",
//				"0000000100000000000000000000000000000000000000000000000000000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_6)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000001000000001000000000000000000000000000000000000000000000000",
//				"0000000100000000000000000000000000000000000000000000000000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_7)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000000000000000000001000000001000000",
//				"0000000000000000000000000000000000000000000000000000000010000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_8)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000000000000000000001000000001000000",
//				"0000000000000000000000000000000000000000000000000000000010000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_9)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000000000000000000000000000100000010",
//				"0000000000000000000000000000000000000000000000000000000000000001");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_10)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000000000000000000000000000000000000000000100000010",
//				"0000000000000000000000000000000000000000000000000000000000000001");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_11)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000011111111000000001111111100000000000000000000000000000000",
//				"0000000000000000111111110000000000000000000000000000000000000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_12)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000011111111000000001111111100000000000000000000000000000000",
//				"0000000000000000111111110000000000000000000000000000000000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_13)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000011111111000000000000000000000000000000000000000000000000",
//				"1111111100000000000000000000000000000000000000000000000000000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_14)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000011111111000000000000000000000000000000000000000000000000",
//				"1111111100000000000000000000000000000000000000000000000000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_15)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000111111110000000011111111000000000000000000000000",
//				"0000000000000000000000001111111100000000000000000000000000000000");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_16)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000000000000111111110000000011111111000000000000000000000000",
//				"0000000000000000000000001111111100000000000000000000000000000000");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_17)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0010000010010000010010000010010000010010000010010000010000000010",
//				"1100000001100000001100000001100000001100000001100000001100000001");
//			Assert::IsTrue(eng->isGameOver());
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_18)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0010000010010000010010000010010000010010000010010000010000000010",
//				"1100000001100000001100000001100000001100000001100000001100000001");
//
//			bool *isBlackWinner = new bool(false);
//			eng->isGameOver();
//			eng->checkIsFirstPlayerWinner(isBlackWinner);
//			Assert::IsTrue(*isBlackWinner);
//		}
//
//		TEST_METHOD(TestCaptureGoEngineMethod_8_19)
//		{
//			CaptureGoEngine::boardSize = 8;
//			CaptureGoEngine::initialize();
//			CaptureGoEngine *eng = new CaptureGoEngine("0000000010010000010010000010010000010010000010010000010000000010",
//				"1100000001100000001100000001100000001100000001100000001100000001");
//			Assert::IsFalse(eng->isGameOver());
//		}
//	};
//}