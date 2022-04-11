#pragma once
#include "Player.h"

namespace gameEngines
{

	class GameEngine
	{
	public:

		Player activePlayer;

		virtual bool IsGameOver() = 0;
		virtual int Evaluate() = 0;
		virtual int GetNumberOfPossibleMoves() = 0;
		virtual GameEngine* GeneratePossibleMoves() = 0;
	};

}

