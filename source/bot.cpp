#include "bot.hpp"

int Bot::mask(char board[3][3]) const {
	int mask = 0;

	for(byte i = 0; i < 3; ++i) {
		for(byte j = 0; j < 3; ++j) {
			mask |= (board[i][j] == 'X') << (pos(i, j) << 1);
			mask |= (board[i][j] == 'O') << ((pos(i, j) << 1) + 1);
		}
	}

	return mask;
}

byte Bot::pos(byte i, byte j) const {
	return i * 3 + j;
}

byte Bot::get(int mask, byte i) const {
	return (mask >> (i << 1)) & 3;
}

void Bot::set(int &mask, byte i, byte turn) const {
	mask &= ~(3 << (i << 1));
	mask |= turn << (i << 1);
}

bool Bot::column(int mask) const {
	if(get(mask, 0) && (get(mask, 0) & get(mask, 3) & get(mask, 6)) == get(mask, 0)) return true;
	if(get(mask, 1) && (get(mask, 1) & get(mask, 4) & get(mask, 7)) == get(mask, 1)) return true;
	if(get(mask, 2) && (get(mask, 2) & get(mask, 5) & get(mask, 8)) == get(mask, 2)) return true;
	return false;
}

bool Bot::row(int mask) const {
	if(get(mask, 0) && (get(mask, 0) & get(mask, 1) & get(mask, 2)) == get(mask, 0)) return true;
	if(get(mask, 3) && (get(mask, 3) & get(mask, 4) & get(mask, 5)) == get(mask, 3)) return true;
	if(get(mask, 6) && (get(mask, 6) & get(mask, 7) & get(mask, 8)) == get(mask, 6)) return true;
	return false;
}

bool Bot::diagonal(int mask) const {
	if(get(mask, 0) && (get(mask, 0) & get(mask, 4) & get(mask, 8)) == get(mask, 0)) return true;
	if(get(mask, 2) && (get(mask, 2) & get(mask, 4) & get(mask, 6)) == get(mask, 2)) return true;
	return false;
}

bool Bot::win(int mask) const {
	return column(mask) || row(mask) || diagonal(mask);
}

bool Bot::draw(int mask) const {
	if(win(mask)) return false;

	for(byte i = 0; i < 9; ++i)
		if(!get(mask, i)) return false;

	return true;
}

char Bot::boardturn(Player turn) const {
	return (turn == X ? 'X' : 'O');
}

Player Bot::flip(byte turn) const {
	return (turn == X ? O : X);
}
