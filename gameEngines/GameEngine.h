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

    protected:
        
        /// <summary>
        /// The answer to the question - whether the game is over?
        /// </summary>
        bool gameOver = false;
        Player winner;

    public:
        /// <summary>
        /// Returns true if the game is over, otherwise returns false
        /// </summary>
        /// <returns>Answer the question: if the game is over? True if yes, false if no.</returns>
        //virtual bool IsGameOver() = 0;
        virtual bool IsGameOver();
        /// <summary>
        /// Evaluation of the game state from the player's point of view
        /// </summary>
        /// <param name="player">The player from whose point of view the evaluation is done</param>
        /// <returns>Game state evaluation value from the selected player's point of view</returns>
        virtual int Evaluate(Player player) = 0;
        /// <summary>
        /// Generates all possible moves without repetition.
        /// </summary>
        /// <param name="count">Number of returned possible game moves</param>
        /// <param name="activePlayer">Information about the active player</param>
        /// <returns>Table of possible moves in the game</returns>
        virtual GameEngine* GeneratePossibleMoves(int& count, Player activePlayer) = 0;
        /// <summary>
        /// Gets the state of the game as a string
        /// </summary>
        /// <returns>String coding the state of the game</returns>
        virtual string GetGameState() = 0;
        /// <summary>
        /// Sets the game state from a given string
        /// </summary>
        /// <param name="gameState">String coding the state of the game</param>
        virtual void SetGameState(std::string newGameState) = 0;
    };

}

#endif