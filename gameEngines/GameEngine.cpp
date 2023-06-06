#include "GameEngine.h"

using namespace std;
using namespace gameEngines;


bool GameEngine::IsGameOver() {
	return this->gameOver;
}

int GameEngine::Evaluate(Player activePlayer) {
	if (this->gameOver)
	{
		if (this->winner == Player::undefined)
			return 0;
		if (this->winner == Player::first)
			return 1;
		else
		{
			return -1;
		}
	}
	// max node
	else if (activePlayer == Player::first)
	{
		return INT_MIN;
	}
	// min node
	else
	{
		return INT_MAX;
	}
}