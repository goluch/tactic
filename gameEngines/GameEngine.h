#ifndef GAMEENGINE
#define GAMEENGINE

#pragma once
#include "Player.h"
#include <sstream>

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool IsGameOver() = 0;
		virtual int Evaluate(Player) = 0;
		virtual int GeneratePossibleMoves(GameEngine&&, Player) = 0;
		virtual std::string GetGameState() = 0;
		virtual void SetGameState(std::string) = 0;
	};

}

#endif