#ifndef BOT_V1_HPP_
#define BOT_V1_HPP_

#include <random>
#include "bot.hpp"

class v1: public Bot {
private:
	int count;
	std::mt19937 ran;
	byte calculate(Player turn, int mask);

public:
	v1();
	~v1() = default;

	byte move(Player turn, char board[3][3]) override;
};

#endif