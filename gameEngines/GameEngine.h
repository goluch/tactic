#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool isGameOver() = 0;
		virtual unsigned int numberOfPossibleMoves(bool) = 0;
		virtual void GeneratePossibleMoves(GameEngine*, bool) = 0;
	};

}

