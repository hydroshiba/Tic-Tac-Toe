#ifndef BOT_V0_HPP_
#define BOT_V0_HPP_

#include <vector>
#include <random>

#include "bot.hpp"

class v0: public Bot {
private:
	std::mt19937 ran;

public:
	v0();
	~v0() = default;

	byte move(Player turn, char board[3][3]) override;
};

#endif