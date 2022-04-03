#pragma once

namespace gameEngines
{

	class GameEngine
	{
	public:

		static unsigned int maxPossibleMoves;

		bool isGameOver();
		void checkIsItAWinner(bool, bool *);
		void checkIsFirstPlayerWinner(bool *);
		unsigned int numberOfPossibleMoves(bool);
		void GeneratePossibleMoves(GameEngine*, bool);
	};

}

