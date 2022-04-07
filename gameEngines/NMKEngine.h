#pragma once
#include "GameEngine.h"

namespace gameEngines
{
	enum Player { undefined, first, second };

	Player operator++(Player& m) {
		return Player(m + 1 % 2);
	}

	class NMKEngine
		: public GameEngine
	{
	public:

		static int N;
		static int M;
		static int K;

		char** board;
		int emptyFieldsCount;
		Player activePlayer;

		bool gameOver = false;

		static unsigned long long endOfBoardMask;
		static unsigned long long leftBorderMask;
		static unsigned long long rightBorderMask;
		static unsigned long long fullBoardMask;
		static unsigned long long possiblyDeadBlackPawns, possiblyDeadWhitePawns;

		NMKEngine();
		~NMKEngine();

		virtual bool IsGameOver();
		virtual int Evaluate();
		virtual int GetNumberOfPossibleMoves(bool);
		virtual GameEngine* GeneratePossibleMoves();

	};

}