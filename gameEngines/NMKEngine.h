#pragma once
#include "GameEngine.h"

namespace gameEngines
{

	class NMKEngine
		: public GameEngine
	{
	public:

		enum Player { undefined, first, second } activePlayer;
		
		Player operator++(int)
		{
			if (this->activePlayer == Player::first) return Player::second;
			if (this->activePlayer == Player::second) return Player::first;
			return Player::undefined;
		}


		static int N;
		static int M;
		static int K;

		char** board;
		int emptyFieldsCount;

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