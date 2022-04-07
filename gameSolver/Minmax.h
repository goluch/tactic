#pragma once
#include "PerformanceCounter.h"

namespace gameSolver
{
	template<typename GameEngine>
	class MinMaxAlg
	{

	public:

		static bool* isItAWinner;

		MinMaxAlg();
		~MinMaxAlg();
		bool Solve(GameEngine, PerformanceCounter* = nullptr);

	protected:
		void StartExecutionTimeMeasurement();
		void StopExecutionTimeMeasurement();
	};

}