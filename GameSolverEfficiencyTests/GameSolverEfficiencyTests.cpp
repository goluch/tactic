#pragma once
// GameSolverEfficiencyTests.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "../gameSolver/ProofNumberSearch.h"
#include "../gameSolver/ProofNumberSearchWrapped.h"
#include "../gameDataStructures/PNSNode.h"
#include "../gameDataStructures/PNSNodeWithoutPointers.h"
#include "../gameEngines/CaptureGoEngine.h"
#include "../gameSolver/exceptions.h"

#define NODE PNSNode<CaptureGoEngine, unsigned int>
#define NODE_WITHOUT_POINTERS PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>

using namespace gameSolver;
using namespace gameDataStructures;
using namespace gameEngines;

int _tmain(int argc, _TCHAR* argv[])
{
	// Przyk³adowy test silnika gry - do skasowania


	/*CaptureGoEngine::boardSize = 3;
	CaptureGoEngine::initialize();
	CaptureGoEngine *eng = new CaptureGoEngine("000101010", "100010001");

	bool res = eng->isGameOver();

	return 0;*/

	// Koniec przyk³adowego silnika gry

	try
	{

		bool result;

		CaptureGoEngine::boardSize = 4;
		CaptureGoEngine::initialize();

		PerformanceCounter pc;

		ProofNumberSearch<NODE> pns;
		result = pns.Solve(NODE(CaptureGoEngine()), true, true, &pc);
		//result = pns.Solve(NODE(CaptureGoEngine()), true, false, &pc);
		//result = pns.Solve(NODE(CaptureGoEngine("1000", "0100")), true, false, &pc);

		//ProofNumberSearchWrapped<NODE_WITHOUT_POINTERS> pns;
		//result = pns.Solve(NODE_WITHOUT_POINTERS(CaptureGoEngine()), true, true, &pc);

		std::cout << "Gracz rozpoczynajacy ";
		result ? std::cout << "wygrywa" : std::cout << "nie wygrywa";
		std::cout << std::endl;
		std::cout << "Liczba wêz³ów przechowywanych w pamieci: " << pc.allExpandedNodes << endl;
		std::cout << "Zaalokowano maksymalnie: " << pc.maxMemoryUsageCount << " bajtów pamiêci" << endl;
		std::cout << "Maksymalne wartoœci proof i disproof w korzeniu to: " << pc.maxProofNumberInRoot << " i " << pc.maxDisProofNumberInRoot << endl;

	}
	catch (std::bad_alloc ex)
	{
		std::cout << "Zabrak³o pamiêci" << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (UnknownGameValueException ex)
	{
		std::cout << "Nieznana wartoœæ" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}

