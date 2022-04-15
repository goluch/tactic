#pragma once
enum class Player { undefined, first, second };

const int playersNumber = 2;

Player operator++(Player&, const int);

Player operator+(const Player&, const int);