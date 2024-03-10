#include "v2.hpp"
#include <iostream>

v2::v2() {
    ran.seed(std::random_device()());

	factorial[0] = 1;
	for(int i = 1; i < 10; ++i) factorial[i] = i * factorial[i - 1];

	weight.resize(factorial[9], 1);
	--weight[index({7, 5, 1, 3, 6, 2, 8, 0, 4})]; 
	std::vector<int> perms(factorial[9]);

	std::iota(perms.begin(), perms.end(), 0);
	std::shuffle(perms.begin(), perms.end(), ran);

	for(int i : perms) order.insert({weight[i], i});
}

int v2::index(std::vector<int> perm) const {
	int ans = 0;

	for(int i = 0; i < 9; ++i) {
		int count = 0;
		for(int j = i + 1; j < 9; ++j)
			if(perm[j] < perm[i]) ++count;
		ans += count * factorial[8 - i];
	}

	return ans;
}

std::vector<int> v2::permutation(int index) const {
	std::vector<int> perm(9);
	for(int i = 0; i < 9; ++i) perm[i] = i;

	for(int i = 0; i < 9; ++i) {
		int j = index / factorial[8 - i];
		std::rotate(perm.begin() + i, perm.begin() + i + j, perm.begin() + i + j + 1);
		index %= factorial[8 - i];
	}

	return perm;
}

byte v2::move(Player turn, char board[3][3]) {
	int mask = this->mask(board);
	byte last, cell = 9, blocks = 0;
	
	std::vector<int> cells = permutation(order.begin()->second);
	order.erase(order.begin()); // Pop permutation with least weight from the set

	for(int i = 0; i < 9; ++i) {
		if(!get(mask, cells[i])) {
			// Winning move
			set(mask, cells[i], turn);
			if(win(mask)) {
				// Winning, half the weight to current permutation
				weight[index(cells)] = std::max(1, weight[index(cells)] >> 1);
				order.insert({weight[index(cells)], index(cells)});
				return cells[i];
			}

			// Blocking move
			set(mask, cells[i], flip(turn));
			if(win(mask)) cell = cells[i], ++blocks; // Save blocking move
			
			set(mask, cells[i], 0);
			last = cells[i]; // Save empty cell
		}
	}

	if(cell == 9) cell = last; // If no critical move found, return last empty cell in the list
	if(blocks > 1) weight[index(cells)] <<= 1; // Losing, double the weight to current permutation
	else weight[index(cells)] = std::max(1, weight[index(cells)] >> 1); // Boring, decrease weight by 1 to current permutation

	order.insert({weight[index(cells)], index(cells)}); // Re-add permutation to the queue
	return cell;
}