#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <vector>
#include <string>

#include "bot.hpp"
#include "bot/v0.hpp"
#include "bot/v1.hpp"
#include "bot/v2.hpp"

class Game {
private:
	std::string title;
	char turn, difficulty;
	char board[3][3];

	Bot* bot;
	v0 random_bot;
	v1 easy_bot;
	v2 medium_bot;
	v2 hard_bot;

	Player player(char turn);

	bool column();
	bool row();
	bool diagonal();

	bool win();
	bool draw();

	void init();
	void show();
	void welcome();

public:
	Game();
	~Game();

	void start();
	void play();
};

#endif