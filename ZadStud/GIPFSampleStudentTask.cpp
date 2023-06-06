#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
//#include "Minmax.h"
//#include "GameEngineExceptions.h"
#include "GIPFEngine.h"
#include "Minmax.h"
using namespace gameSolver;

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
                string checkPawnsNumRes = eng->CheckPawnsNumber();
                if (checkPawnsNumRes == "BOARD_STATE_OK")
                {
                    int kInRowNum = eng->CheckKInRow();
                    if (kInRowNum)
                    {
                        cout << "ERROR_FOUND_" << kInRowNum << "_ROW" << ((kInRowNum > 1) ? "S" : "") << "_OF_LENGTH_K";
                    }
                    else
                    {
                        cout << checkPawnsNumRes;
                    }
                }
                else
                {
                    cout << checkPawnsNumRes;
                }
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
        if (command == "GEN_ALL_POS_MOV")
        {
            int possibmeMovesCount;
            GIPFEngine* possibmeMoves = (GIPFEngine*)eng->GeneratePossibleMoves( possibmeMovesCount);
            for (int i = 0; i < possibmeMovesCount; i++)
            {
                cout << possibmeMoves[i].GetGameState();
            }
            delete[] possibmeMoves;
        }
        if (command == "GEN_ALL_POS_MOV_NUM")
        {
            int possibmeMovesCount;
            GIPFEngine* possibmeMoves  = (GIPFEngine*)eng->GeneratePossibleMoves(possibmeMovesCount);
            cout << possibmeMovesCount << "_UNIQUE_MOVES" << endl;
            delete[] possibmeMoves;
        }
        if (command == "GEN_ALL_POS_MOV_EXT")
        {
            int possibmeMovesCount;
            eng->cutIfGameOver = true;
            GIPFEngine* possibmeMoves = (GIPFEngine*)eng->GeneratePossibleMoves(possibmeMovesCount);
            for (int i = 0; i < possibmeMovesCount; i++)
            {
                cout << possibmeMoves[i].GetGameState();
            }
            delete[] possibmeMoves;
        }
        if (command == "GEN_ALL_POS_MOV_EXT_NUM")
        {
            int possibmeMovesCount;
            eng->cutIfGameOver = true;
            GIPFEngine* possibmeMoves = (GIPFEngine*)eng->GeneratePossibleMoves(possibmeMovesCount);
            cout << possibmeMovesCount << "_UNIQUE_MOVES" << endl;
            delete[] possibmeMoves;
        }
        if (command == "IS_GAME_OVER")
        {
            if (eng->IsGameOver())
            {
                cout << "THE_WINNER_IS_" << (eng->Evaluate(Player::first) == 1 ? "WHITE" : "BLACK") << endl;
            }
            else
            {
                cout << "GAME_IN_PROGRESS" << endl;
            }
        }
        if (command == "SOLVE_GAME_STATE")
        {
            MinmaxAlg<GIPFEngine> minMaxAlg;
            int result = minMaxAlg.Solve(*eng, eng->activePlayer);
            switch (result)
            {
            case -1:
                cout << "BLACK_HAS_WINNING_STRATEGY" << endl;
                break;
            case 0:
                cout << "BOTH_PLAYERS_TIE" << endl;
                break;
            case 1:
                cout << "WHITE_HAS_WINNING_STRATEGY" << endl;
                break;
            default:
                break;
            }
        }
        if (command == "WINNING_SEQUENCE_EXIS")
        {

        }
    }
    delete eng;
}