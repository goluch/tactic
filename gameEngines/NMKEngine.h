#pragma once
#include <assert.h>
#include <vector>
#include "BoardIndex.h"
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
        static bool showNodes;
        static bool cutIfGameOver;
        static string Info;

        NMKEngine();
        //NMKEngine(NMKEngine&);
        ~NMKEngine();

        virtual bool IsGameOver();
        virtual int Evaluate(Player);
        virtual GameEngine* GeneratePossibleMoves(int&, Player);
        virtual string GetGameState();
        virtual void SetGameState(string);

    private:

        int emptyFieldsCount;
        BoardIndex threatIndex;
        int foundedThreats;
        vector<vector<char>> board;
        Player winner;

        bool Check_K_InRow(NMKEngine*, int, int, Player);

    };

}