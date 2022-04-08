#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		virtual bool IsGameOver() = 0;
		virtual int Evaluate() = 0;
		virtual int GetNumberOfPossibleMoves(bool) = 0;
		virtual GameEngine* GeneratePossibleMoves() = 0;
	};

}

