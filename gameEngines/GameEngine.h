#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		static unsigned int maxPossibleMoves;

		virtual bool isGameOver() = 0;
		virtual void checkIsItAWinner(bool, bool*) = 0;
		virtual void checkIsFirstPlayerWinner(bool*) = 0;
		virtual unsigned int numberOfPossibleMoves(bool) = 0;
		virtual void GeneratePossibleMoves(GameEngine*, bool) = 0;
	};

}

