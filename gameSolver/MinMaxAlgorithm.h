#pragma once
#include "PerformanceCounter.h"

namespace gameSolver
{
	template<typename G>
	class MinMaxAlg
	{

	public:

		static bool* isItAWinner;

		MinMaxAlg();
		~MinMaxAlg();
		bool Solve(G, PerformanceCounter* = nullptr);

	protected:
		void startExecutionTimeMeasurement();
		void stopExecutionTimeMeasurement();
	};

}