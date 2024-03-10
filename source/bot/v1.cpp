#include "v1.hpp"

v1::v1() : count(0) {
    this->ran.seed(std::random_device()());
}

byte v1::calculate(Player turn, int mask) {
	int cell = ran() % 9;

	if(get(mask, cell) == 0) {
		// Winning move
		set(mask, cell, turn);
		if(win(mask)) return cell;

		// Blocking move
		set(mask, cell, flip(turn));
		if(win(mask)) return cell;

		++count;
		if(count > 18) return cell; // Return if done enough random iterations
		set(mask, cell, 0);
	}
	
	return calculate(turn, mask);
}

byte v1::move(Player turn, char board[3][3]) {
	count = 0;
	int mask = this->mask(board);
	return calculate(turn, mask);
}