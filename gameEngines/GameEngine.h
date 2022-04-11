#pragma once
#include "Player.h"

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool IsGameOver() = 0;
		virtual int Evaluate(Player) = 0;
		virtual int GetNumberOfPossibleMoves(Player) = 0;
		virtual GameEngine* GeneratePossibleMoves(Player) = 0;
		virtual std::string  PrintGameState() = 0;
	};

}

