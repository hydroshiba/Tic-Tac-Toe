#ifndef BOT_V2_HPP_
#define BOT_V2_HPP_

#include <algorithm>
#include <vector>
#include <random>
#include <set>
#include <utility>

#include "bot.hpp"

class v2: public Bot {
private:
	std::mt19937 ran;
	
	int factorial[10];
	std::vector<int> weight;
	std::set<std::pair<int, int>> order;
	
	int index(std::vector<int> perm) const;
	std::vector<int> permutation(int index) const;

public:
	v2();
	~v2() = default;

	byte move(Player turn, char board[3][3]) override;
};

#endif