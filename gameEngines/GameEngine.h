#ifndef GAMEENGINE
#define GAMEENGINE

#pragma once
#include "Player.h"
#include <sstream>

using namespace std;

namespace gameEngines
{

    class GameEngine
    {
    public:

        virtual bool IsGameOver() = 0;
        virtual int Evaluate(Player) = 0;
        virtual GameEngine* GeneratePossibleMoves(int&, Player) = 0;
        virtual string GetGameState() = 0;
        virtual void SetGameState(std::string) = 0;
    };

}

#endif