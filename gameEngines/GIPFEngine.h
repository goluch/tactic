#pragma once
#include <vector>
#include "Player.h"
#include "GameEngine.h"
#include "GameEngineExceptions.h"
namespace gameEngines
{


    class GIPFEngine
        : public GameEngine
    {
    public:

		GIPFEngine();
		~GIPFEngine();

		virtual int Evaluate(Player);
		virtual GameEngine* GeneratePossibleMoves(int& count, Player activePlayer);
		virtual string SetGameState(istream& newGameState);
		virtual string GetGameState();

		string CheckPawnsNumber();

    private:

		//border is the outer fields of the board intended for pieces added at the beginning of the move
		int s;
		int k;
		int gw;
		int gb;
		int gw_res;
		int gb_res;
		int diag;
		char value;
		Player activePlayer;
		vector<vector<char>> board;
		string info;
		const int border = 1;;
		//always starts white
		static const char firstPlayerField;
		static const char secondPlayerField;
		static const char startField;
		static const char emptyField;
		static const char forbiddenField;

    };

}