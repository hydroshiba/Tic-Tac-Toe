#include "v3.hpp"
#include <iostream>

v3::v3() {
	this->ran.seed(std::random_device()());

	memset(eval, 255, sizeof(eval));
	memset(trace, 255, sizeof(trace));

	calculate(X, 0);
	calculate(O, 0);
}

void v3::calculate(Player turn, int mask) {
	byte &res = eval[turn][mask];
	byte &cell = trace[turn][mask];
	if(res != 255) return;

	// 0 = X win, 1 = draw, 2 = X lose (higher value = worse)
	if(win(mask)) {
		res = (turn == X ? 2 : 0);
		return;
	}

	if(draw(mask)) {
		res = 1;
		return;
	}

	// Calculate using Dynamic Programming
	if(turn == X) res = 2;
	else res = 0;

	for(int i = 0; i < 9; ++i) if(!get(mask, i)) {
		int new_mask = mask;
		set(new_mask, i, turn);

		// If X turn then maximize chances of winning (minimize the value)
		if(turn == X) {
			calculate(O, new_mask);
			int val = eval[O][new_mask];

			if(val < res) {
				res = val;
				cell = i;
			}
			else if(val == res) cell = ((ran() & 1) ? cell : i);
		}
		// If O turn then minimize chances of winning (maximize the value)
		else {
			calculate(X, new_mask);
			int val = eval[X][new_mask];

			if(val > res) {
				res = val;
				cell = i;
			}
			else if(val == res) cell = ((ran() & 1) ? cell : i);
		}
	}
}

byte v3::move(Player turn, char board[3][3]) {
	int mask = this->mask(board);
	return trace[turn][mask];
}