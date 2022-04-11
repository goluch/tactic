#pragma once
#include<vector>
#include "Player.h"

namespace gameEngines
{

	class GameEngine
	{
	public:

		int emptyFieldsCount;
		Player activePlayer;
		std::vector<std::vector<char>> board;
		virtual bool IsGameOver() = 0;
		virtual int Evaluate() = 0;
		virtual int GetNumberOfPossibleMoves() = 0;
		virtual GameEngine* GeneratePossibleMoves() = 0;
	};

}

