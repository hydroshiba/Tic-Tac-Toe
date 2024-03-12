#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>

#include "bot.hpp"
#include "bot/v0.hpp"
#include "bot/v1.hpp"
#include "bot/v2.hpp"
#include "bot/v3.hpp"

class Game {
private:
	std::string title;
	char board[3][3];

	Bot* p1;
	Bot* p2;

	Player player(char turn);

	bool column();
	bool row();
	bool diagonal();

	bool win();
	bool draw();

	void init();
	void show();
	void welcome();

	Bot* get_bot(char diff);

public:
	Game();
	~Game();

	void start();
	void play();
	void simulate();
};

#endif