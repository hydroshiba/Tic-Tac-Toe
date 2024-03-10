#include "v0.hpp"

v0::v0() {
	this->ran.seed(std::random_device()());
}

byte v0::move(Player turn, char board[3][3]) {
	int mask = this->mask(board);
	std::vector<byte> moves;

	for(byte i = 0; i < 9; ++i)
		if(get(mask, i) == 0) moves.push_back(i);

	return moves[this->ran() % moves.size()];
}