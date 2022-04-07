#pragma once

#include <time.h>
#include "MinMax.h"
#include "GameEngine.h"
#include "limits.h"

using namespace gameSolver;
using namespace gameEngines;

template<typename GameEngine>
bool MinMaxAlg<GameEngine>::Solve(GameEngine gE, PerformanceCounter* pC)
{
#ifdef _DEBUG
	if (pc)
	{
		//liczymy performance
	}
#endif

};
