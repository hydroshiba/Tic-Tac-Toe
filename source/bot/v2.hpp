#ifndef BOT_V2_HPP_
#define BOT_V2_HPP_

#include <algorithm>
#include <vector>
#include <random>

#include "bot.hpp"

class v2: public Bot {
private:
	std::mt19937 ran;

	int factorial[10];
	std::vector<int> order, weight;

	int index(std::vector<int> perm);
	std::vector<int> permutation(int index);

	void reorder();

public:
	v2();
	~v2() = default;

	byte move(Player turn, char board[3][3]) override;
};

#endif