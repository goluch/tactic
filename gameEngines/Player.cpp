#include "Player.h"

Player operator++(Player& p, int)
{
	if (p == Player::undefined)
	{
		return Player::undefined;
	}
	else
	{
		int nextP = static_cast<int>(p) + 1;
		if (nextP == playersNumber + 1) { nextP = 1; }
		p = static_cast<Player>(nextP);
		return p;
	}
}