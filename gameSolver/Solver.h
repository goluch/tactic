#pragma once
#include "PerformanceCounter.h"

namespace gameSolver
{
	// GameEngine to obiekt silnika gry, reprezentuje kompletny stan grê niekoniecznie pocz¹tkowy.
	template<typename GameEngine>
	class Solver
	{

	public:
		// Metoda Solve odpowiada na pytanie czy dla danego stanu gry, gracz aktywny wygrywa.
		virtual bool Solve(GameEngine, PerformanceCounter* = nullptr) = 0;

	protected:
		virtual void StartExecutionTimeMeasurement() = 0;
		virtual void StopExecutionTimeMeasurement() = 0;
	};

}

