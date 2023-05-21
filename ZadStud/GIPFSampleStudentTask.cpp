#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
//#include "Minmax.h"
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
    GIPFEngine* eng = new GIPFEngine();
    while (cin >> command)
    {
        if (command == "LOAD_GAME_BOARD")
        {
            string res;
            //try
            {
                res = eng->SetGameState(cin);
            }
            /*catch (WrongGameStateSettingsException e)
            {
                cout << e.what() << endl;
                continue;
            }*/
            if (res == "OK")
            {
                cout << eng->CheckPawnsNumber() << endl;
            }
            else
            {
                cout << res;
            }
            cout << endl;
        }
        if (command == "PRINT_GAME_BOARD")
        {
            cout << eng->GetGameState() << endl;
        }
        if (command == "DO_MOVE")
        {
            string move;
            cin >> move;
            cout << eng->DoMove(move) << endl;
        }
    }
    delete eng;
}