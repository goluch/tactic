#pragma once
#include <assert.h>
#include <vector>
#include "Player.h"
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
		static bool ShowLeafes;

		NMKEngine();
		~NMKEngine();

		virtual bool IsGameOver();
		virtual int Evaluate(Player);
		virtual int GetNumberOfPossibleMoves(Player);
		virtual GameEngine* GeneratePossibleMoves(Player);
		bool Check_K_InRow(NMKEngine*, int, int, Player);
		virtual std::string PrintGameState();

	private:

		int emptyFieldsCount;
		bool gameOver = false;
		Player winner;
		std::vector<std::vector<char>> board;

	};

}