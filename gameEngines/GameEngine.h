#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool IsGameOver() = 0;
		virtual int Evaluate();
		virtual int GetNumberOfPossibleMoves(bool) = 0;
		virtual GameEngine* GeneratePossibleMoves() = 0;
	};

}

