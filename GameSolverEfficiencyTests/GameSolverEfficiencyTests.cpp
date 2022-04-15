#pragma once
// GameSolverEfficiencyTests.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "Minmax.h"
//#include "exceptions.h"
#include "NMKEngine.h"
using namespace gameEngines;
//using namespace gameSolver;

//#define NODE PNSNode<CaptureGoEngine, unsigned int>
//#define NODE_WITHOUT_POINTERS PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>

using namespace std;
//using namespace gameSolver;
//using namespace gameDataStructures;
using namespace gameEngines;

int _tmain(int argc, _TCHAR* argv[])
{
	// Przyk�adowy test silnika gry - do skasowania


	/*CaptureGoEngine::boardSize = 3;
	CaptureGoEngine::initialize();
	CaptureGoEngine *eng = new CaptureGoEngine("000101010", "100010001");

	bool res = eng->isGameOver();

	return 0;*/

	// Koniec przyk�adowego silnika gry

	//try
	//{
		NMKEngine::N = 3;
		NMKEngine::M = 4;
		NMKEngine::K = 3;
		//NMKEngine::ShowNodes = true;
		NMKEngine nmkEng;
		//for (int i = 0; i < possibleMovesCount; i++)
		//{
		//	cout << endl;
		//	cout << newGames[i].GetGameState() << endl;
		//}
		//nmkEng.SetGameState();
		//nmkEng.SetGameState("2 1 2 1 2 1 0 0 0");
		gameSolver::MinmaxAlg<NMKEngine> mmAlg;
		cout << "Result: " << mmAlg.Solve(nmkEng, Player::first);

		//bool result;

	//	CaptureGoEngine::boardSize = 4;
	//	//CaptureGoEngine::initialize();

	//	//PerformanceCounter pc;

	//	P//roofNumberSearch<NODE> pns;
	//	result = pns.Solve(NODE(CaptureGoEngine()), true, true, &pc);
	//	//result = pns.Solve(NODE(CaptureGoEngine()), true, false, &pc);
	//	//result = pns.Solve(NODE(CaptureGoEngine("1000", "0100")), true, false, &pc);

	//	//ProofNumberSearchWrapped<NODE_WITHOUT_POINTERS> pns;
	//	//result = pns.Solve(NODE_WITHOUT_POINTERS(CaptureGoEngine()), true, true, &pc);

	//	std::cout << "Gracz rozpoczynajacy ";
	//	result ? std::cout << "wygrywa" : std::cout << "nie wygrywa";
	//	std::cout << std::endl;
	//	std::cout << "Liczba w�z��w przechowywanych w pamieci: " << pc.allExpandedNodes << endl;
	//	std::cout << "Zaalokowano maksymalnie: " << pc.maxMemoryUsageCount << " bajt�w pami�ci" << endl;
	//	std::cout << "Maksymalne warto�ci proof i disproof w korzeniu to: " << pc.maxProofNumberInRoot << " i " << pc.maxDisProofNumberInRoot << endl;

	//}
	//catch (std::bad_alloc ex)
	//{
	//	std::cout << "Zabrak�o pami�ci" << std::endl;
	//	exit(EXIT_FAILURE);
	//}
	//catch (UnknownGameValueException ex)
	//{
	//	std::cout << "Nieznana warto��" << std::endl;
	//	exit(EXIT_FAILURE);
	//}
	return 0;
}

