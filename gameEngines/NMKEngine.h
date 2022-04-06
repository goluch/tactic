#pragma once
#include "GameEngine.h"

namespace gameEngines
{

	class NMKEngine
		: public GameEngine
	{

	public:

		unsigned long long blackPawns;
		unsigned long long whitePawns;

		static unsigned int N;
		static unsigned int M;
		static unsigned int K;
		static unsigned int fieldsNumber;

		static unsigned long long endOfBoardMask;
		static unsigned long long leftBorderMask;
		static unsigned long long rightBorderMask;
		static unsigned long long fullBoardMask;
		static unsigned long long possiblyDeadBlackPawns, possiblyDeadWhitePawns;

		static void initialize();

		virtual bool isGameOver();
		virtual void checkIsItAWinner(bool, bool*);
		virtual void checkIsFirstPlayerWinner(bool*);
		virtual unsigned int numberOfPossibleMoves(bool);
		virtual void GeneratePossibleMoves(GameEngine*, bool);

		NMKEngine();
		NMKEngine(unsigned long long, unsigned long long);
		NMKEngine(char *, char *);

	};

}