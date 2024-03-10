#ifndef BOT_V3_HPP_
#define BOT_V3_HPP_

#include <cstring>
#include <vector>
#include <random>

#include "bot.hpp"

class v3: public Bot {
private:
	std::mt19937 ran;
	byte eval[3][2 << 18], trace[3][2 << 18];

	void calculate(Player turn, int mask);

public:
	v3();
	~v3() = default;

	byte move(Player turn, char board[3][3]) override;
};

#endif