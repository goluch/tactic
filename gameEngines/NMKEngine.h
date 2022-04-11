#pragma once
#include "GameEngine.h"

namespace gameEngines
{

	class NMKEngine
		: public GameEngine
	{
	public:

		static int N;
		static int M;
		static int K;

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
		virtual int GetNumberOfPossibleMoves();
		virtual GameEngine* GeneratePossibleMoves();
	};

}