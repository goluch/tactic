#pragma once
#include "PerformanceCounter.h"

namespace gameSolver
{
	template<typename GameEngine>
	class NegamaxAlg
	{

	public:

		static bool* isItAWinner;

		NegamaxAlg();
		~NegamaxAlg();
		bool Solve(PerformanceCounter* = nullptr);

	protected:
		void StartExecutionTimeMeasurement();
		void StopExecutionTimeMeasurement();
	};

}