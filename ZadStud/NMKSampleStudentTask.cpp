﻿//NMKEngine sample student task

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "Minmax.h"
#include "NMKEngine.h"

using namespace std;
using namespace gameEngines;
using namespace gameSolver;

int _tmainNOT_ACTIVE(int argc, _TCHAR* argv[])
{


    string command;
    while (cin >> command)
    {
        if (command == "GEN_ALL_POS_MOV")
        {
            cin >> NMKEngine::N;
            cin >> NMKEngine::M;
            cin >> NMKEngine::K;
            int activePlayer;
            cin >> activePlayer;
            NMKEngine nmkEng;
            string number;
            ostringstream gameState;
            for (int i = 0; i < NMKEngine::N * NMKEngine::M; i++)
            {
                if (i)
                {
                    gameState << " ";
                }
                cin >> number;
                gameState << number;
            }
            cout << nmkEng.SetGameState(stringstream(gameState.str()));
            int possibmeMovesCount;
            NMKEngine* possibmeMoves = (NMKEngine*)nmkEng.GeneratePossibleMoves(possibmeMovesCount, (Player)activePlayer);
            cout << possibmeMovesCount << endl;
            for (int i = 0; i < possibmeMovesCount; i++)
            {
                cout << possibmeMoves[i].GetGameState();
            }
            continue;
        }
        if (command == "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")
        {
            cin >> NMKEngine::N;
            cin >> NMKEngine::M;
            cin >> NMKEngine::K;
            NMKEngine::cutIfGameOver = true;
            int activePlayer;
            cin >> activePlayer;
            NMKEngine nmkEng;
            string number;
            ostringstream gameState;
            for (int i = 0; i < NMKEngine::N * NMKEngine::M; i++)
            {
                if (i)
                {
                    gameState << " ";
                }
                cin >> number;
                gameState << number;
            }
            cout << nmkEng.SetGameState(stringstream(gameState.str()));
            int possibmeMovesCount;
            NMKEngine* possibmeMoves = (NMKEngine*)nmkEng.GeneratePossibleMoves(possibmeMovesCount, (Player)activePlayer);
            cout << possibmeMovesCount << endl;
            for (int i = 0; i < possibmeMovesCount; i++)
            {
                cout << possibmeMoves[i].GetGameState();
            }
            continue;
        }
        if (command == "SOLVE_GAME_STATE")
        {
            cin >> NMKEngine::N;
            cin >> NMKEngine::M;
            cin >> NMKEngine::K;
            NMKEngine::cutIfGameOver = true;
            int activePlayer;
            cin >> activePlayer;
            NMKEngine nmkEng;
            string number;
            ostringstream gameState;
            for (int i = 0; i < NMKEngine::N * NMKEngine::M; i++)
            {
                if (i)
                {
                    gameState << " ";
                }
                cin >> number;
                gameState << number;
            }
            cout << nmkEng.SetGameState(stringstream(gameState.str()));
            MinmaxAlg<NMKEngine> minMaxAlg;
            minMaxAlg.cutIfPossible = true;
            int result = minMaxAlg.Solve(nmkEng, (Player)activePlayer);
            switch (result)
            {
            case -1:
                cout << "SECOND_PLAYER_WINS" << endl;
                break;
            case 0:
                cout << "BOTH_PLAYERS_TIE" << endl;
                break;
            case 1:
                cout << "FIRST_PLAYER_WINS" << endl;
                break;
            default:
                break;
            }
            continue;
        }
        throw new exception("Bad command");
    }
    cout.flush();
}
