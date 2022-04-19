#pragma once
// GameSolverEfficiencyTests.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "Minmax.h"
#include "NMKEngine.h"

using namespace std;
using namespace gameEngines;
using namespace gameSolver;

int _tmain(int argc, _TCHAR* argv[])
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
			nmkEng.SetGameState(gameState.str());
			int possibmeMovesCount;
			NMKEngine* possibmeMoves = (NMKEngine*)nmkEng.GeneratePossibleMoves(possibmeMovesCount, (Player) activePlayer);
			cout << possibmeMovesCount << endl;
			for (int i = 0; i < possibmeMovesCount; i++)
			{
				cout << possibmeMoves[i].GetGameState();
			}
			continue;
		}
		throw new exception("Bad command");
	}
	cout.flush();
}

