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
		static int border;
		static bool ShowNodes;

		NMKEngine();
		//NMKEngine(NMKEngine&);
		~NMKEngine();

		virtual bool IsGameOver();
		virtual int Evaluate(Player);
		virtual int GeneratePossibleMoves(GameEngine&&, Player);
		bool Check_K_InRow(NMKEngine*, int, int, Player);
		virtual std::string GetGameState();
		virtual void SetGameState(std::string);

	private:

		int emptyFieldsCount;
		std::vector<std::vector<char>> board;
		bool gameOver = false;
		Player winner;

	};

}