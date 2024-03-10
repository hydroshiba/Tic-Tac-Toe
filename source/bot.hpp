#ifndef BOT_HPP_
#define BOT_HPP_

using byte = unsigned char;

enum Player {
	X = 1, O = 2
};

class Bot {
protected:
	int mask(char board[3][3]) const;

	byte pos(byte i, byte j) const;
	byte get(int mask, byte i) const;
	void set(int &mask, byte i, byte turn) const;

	bool column(int mask) const;
	bool row(int mask) const;
	bool diagonal(int mask) const;

	bool win(int mask) const;
	bool draw(int mask) const;

	char boardturn(Player turn) const;
	Player flip(byte turn) const;

public:
	Bot() = default;
	~Bot() = default;

	virtual byte move(Player turn, char board[3][3]) = 0;
};

#endif