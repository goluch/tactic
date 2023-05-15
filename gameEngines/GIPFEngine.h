#pragma once
#include "Player.h"
#include "GameEngine.h"
namespace gameEngines
{
    class GIPFEngine
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

        GIPFEngine();
        ~GIPFEngine();

        virtual bool IsGameOver();
        virtual int Evaluate(Player);
        virtual GameEngine* GeneratePossibleMoves(int& count, Player activePlayer);
        virtual string GetGameState();
        virtual void SetGameState(string);

    private:

    };

}