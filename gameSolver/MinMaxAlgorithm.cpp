#pragma once

#include <time.h>
#include "MinMaxAlgorithm.h"
#include "CaptureGoEngine.h"
#include "limits.h"

using namespace gameSolver;
using namespace gameEngines;

template<typename G>
bool MinMaxAlg<G>::Solve(G, PerformanceCounter* pc)
{
	{
#ifdef _DEBUG
		if (pc)
		{
			//liczymy performance
		}
#endif
	}
};
