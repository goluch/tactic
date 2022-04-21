#pragma once
// GameSolverEfficiencyTests.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "../gameSolver/Minmax.h"
#include "../gameEngines/NMKEngine.h"

using namespace std;
using namespace gameEngines;
using namespace gameSolver;

void GenerateAllBoardsWithCommand(int N, int M, int K, bool cutIfGameOverInEngine, bool cutIfGameOverInAlgorithm, string command)
{
	int lastN = NMKEngine::N;
	int lastM = NMKEngine::M;
	int lastK = NMKEngine::K;
	bool lastShownodes = NMKEngine::showNodes;
	bool lastCutIfGameOver = NMKEngine::cutIfGameOver;
	string lastInfo = NMKEngine::Info;
	NMKEngine::N = N;
	NMKEngine::M = M;
	NMKEngine::K = K;
	NMKEngine::showNodes = true;
	NMKEngine::cutIfGameOver = cutIfGameOverInEngine;
	NMKEngine::Info = static_cast<std::ostringstream&>(std::ostringstream().seekp(0) << command << " " << NMKEngine::N << " " << NMKEngine::M << " " << NMKEngine::K).str();

	NMKEngine nmkEng;

	gameSolver::cutIfGameOver = cutIfGameOverInAlgorithm;
	MinmaxAlg<NMKEngine> mmAlg;
	mmAlg.Solve(nmkEng, Player::first);

	NMKEngine::N = lastN;
	NMKEngine::M = lastM;
	NMKEngine::K = lastK;
	NMKEngine::showNodes = lastShownodes;
	NMKEngine::Info = lastInfo;
	NMKEngine::cutIfGameOver = lastCutIfGameOver;
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//GenerateAllBoardsWithCommand(2, 2, 2, false, false, "GEN_ALL_POS_MOV");
	//GenerateAllBoardsWithCommand(2, 3, 2, false, false, "GEN_ALL_POS_MOV");
	//GenerateAllBoardsWithCommand(3, 3, 2, false, false, "GEN_ALL_POS_MOV");
	//GenerateAllBoardsWithCommand(3, 3, 3, true, true, "GEN_ALL_POS_MOV");
	//GenerateAllBoardsWithCommand(3, 4, 3, true, true, "GEN_ALL_POS_MOV");
	//GenerateAllBoardsWithCommand(4, 4, 3, true, true, "GEN_ALL_POS_MOV");

	//GenerateAllBoardsWithCommand(2, 2, 2, false, false, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
	//GenerateAllBoardsWithCommand(2, 3, 2, false, false, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
	//GenerateAllBoardsWithCommand(3, 3, 2, false, false, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
	//GenerateAllBoardsWithCommand(3, 3, 3, true, true, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
	//GenerateAllBoardsWithCommand(3, 4, 3, true, true, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
	GenerateAllBoardsWithCommand(4, 4, 3, true, true, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER");
}

