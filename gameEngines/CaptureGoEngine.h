#pragma once
#include "GameEngine.h"

namespace gameEngines
{

	class CaptureGoEngine
		: public GameEngine
	{
		void checkBreath(unsigned long long, unsigned long long *);

	public:

		unsigned long long blackPawns;
		unsigned long long whitePawns;

		static unsigned int boardSize;
		static unsigned int fieldsNumber;

		static unsigned long long endOfBoardMask;
		static unsigned long long leftBorderMask;
		static unsigned long long rightBorderMask;
		static unsigned long long fullBoardMask;
		static unsigned long long possiblyDeadBlackPawns, possiblyDeadWhitePawns;

		static void initialize();

		CaptureGoEngine();
		CaptureGoEngine(unsigned long long, unsigned long long);
		CaptureGoEngine(char *, char *);

		bool isGameOver();
		void checkIsItAWinner(bool, bool *);
		void checkIsFirstPlayerWinner(bool *);
		unsigned int numberOfPossibleMoves(bool);
		void GeneratePossibleMoves(CaptureGoEngine*, bool);
		unsigned long long pawnsFromStringToLong(char *);
	};

}