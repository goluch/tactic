#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "Minmax.h"
//#include "exceptions.h"
#include "GIPFEngine.h"

//#define NODE PNSNode<CaptureGoEngine, unsigned int>
//#define NODE_WITHOUT_POINTERS PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>

using namespace std;
//using namespace gameSolver;
//using namespace gameDataStructures;
using namespace gameEngines;

int _tmain(int argc, _TCHAR* argv[])
{
    string command;
    while (cin >> command)
    {
        if (command == "LOAD_GAME_BOARD")
        {
			int s; //board size
			int k; //k-in-row
			int gw; //white pawns number
			int gb; //black pawns number
			cin >> s >> k >> gw >> gb;
			GIPFEngine* eng = new GIPFEngine(s, k, gw, gb);
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
			eng->SetGameState(properString);
			//Assert::AreEqual(0, eng->CheckPawnsNumber());
			delete eng;
        }
    }
}