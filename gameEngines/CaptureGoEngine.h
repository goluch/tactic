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

		static int boardSize;
		static int fieldsNumber;
		static int maxPossibleMoves;

		static unsigned long long endOfBoardMask;
		static unsigned long long leftBorderMask;
		static unsigned long long rightBorderMask;
		static unsigned long long fullBoardMask;
		static unsigned long long possiblyDeadBlackPawns, possiblyDeadWhitePawns;

		virtual bool IsGameOver();
		virtual int Evaluate();
		virtual void CheckIsItAWinner(bool, bool*);
		virtual void CheckIsFirstPlayerWinner(bool*);
		virtual int GetNumberOfPossibleMoves(bool);
		virtual void GeneratePossibleMoves(GameEngine*, bool);

		CaptureGoEngine();
		CaptureGoEngine(unsigned long long, unsigned long long);
		CaptureGoEngine(char *, char *);

		unsigned long long GetPawnsFromStringToLong(char *);
	};

}