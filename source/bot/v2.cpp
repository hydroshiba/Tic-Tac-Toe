#include "v2.hpp"
#include <iostream>

v2::v2() {
    ran.seed(std::random_device()());

	factorial[0] = 1;
	for(int i = 1; i < 10; ++i) factorial[i] = i * factorial[i - 1];

	weight.resize(factorial[9]);
	for(int i = 0; i < factorial[9]; ++i) order.push_back(i);

	// Default configuration
	--weight[index({7, 5, 1, 3, 6, 2, 8, 0, 4})];
	reorder();
}

int v2::index(std::vector<int> perm) {
	int ans = 0;

	for(int i = 0; i < 9; ++i) {
		int count = 0;
		for(int j = i + 1; j < 9; ++j)
			if(perm[j] < perm[i]) ++count;
		ans += count * factorial[8 - i];
	}

	return ans;
}

std::vector<int> v2::permutation(int index) {
	std::vector<int> perm(9);
	for(int i = 0; i < 9; ++i) perm[i] = i;

	for(int i = 0; i < 9; ++i) {
		int j = index / factorial[8 - i];
		std::rotate(perm.begin() + i, perm.begin() + i + j, perm.begin() + i + j + 1);
		index %= factorial[8 - i];
	}

	return perm;
}

void v2::reorder() {
	std::shuffle(order.begin(), order.end(), ran);
	std::sort(order.begin(), order.end(), [&](int a, int b) {
		return weight[a] < weight[b];
	});
}

byte v2::move(Player turn, char board[3][3]) {
	int mask = this->mask(board);
	byte last, cell = 9, blocks = 0;
	
	std::vector<int> cells = permutation(order[0]);
	for(int i : cells) std::cout << i << ' ';
	std::cout << '\n';

	for(int i = 0; i < 9; ++i) {
		if(!get(mask, cells[i])) {
			// Winning move
			set(mask, cells[i], turn);
			if(win(mask)) {
				--weight[index(cells)]; // Winning, decrease weight to current permutation
				reorder();
				return cells[i]; // Return immediately
			}

			// Blocking move
			set(mask, cells[i], flip(turn));
			if(win(mask)) cell = cells[i], ++blocks; // Save blocking move
			
			set(mask, cells[i], 0);
			last = cells[i]; // Save empty cell
		}
	}

	// Losing, increase weight to current permutation
	if(blocks > 1) {
		++weight[index(cells)];
		reorder();
	}

	if(cell == 9) cell = last; // If no critical move found, return last empty cell in the list
	return cell;
}