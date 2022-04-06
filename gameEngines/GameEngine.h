#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool isGameOver() = 0;
		virtual unsigned int numberOfPossibleMoves(bool) = 0;
		virtual GameEngine* GeneratePossibleMoves() = 0;
	};

}

