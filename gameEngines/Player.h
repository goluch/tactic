#pragma once
enum class Player { undefined, first, second };

const int playersNumber = 2;

Player operator++(Player&, int);

Player operator+(Player&, const int);