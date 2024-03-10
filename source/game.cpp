#include "game.hpp"

Game::Game() : bot(nullptr) {
	title = R"(
	 ______  __  ______       ______  ______  ______       ______  ______  ______    
	/\__  _\/\ \/\  ___\     /\__  _\/\  __ \/\  ___\     /\__  _\/\  __ \/\  ___\   
	\/_/\ \/\ \ \ \ \____    \/_/\ \/\ \  __ \ \ \____    \/_/\ \/\ \ \/\ \ \  __\   
	   \ \_\ \ \_\ \_____\      \ \_\ \ \_\ \_\ \_____\      \ \_\ \ \_____\ \_____\ 
	    \/_/  \/_/\/_____/       \/_/  \/_/\/_/\/_____/       \/_/  \/_____/\/_____/
	)";

	init();
	welcome();
}

Game::~Game() {}

Player Game::player(char turn) {
    byte value = (turn == 'X') | ((turn == 'O') << 1);
	return static_cast<Player>(value);
}

bool Game::column() {
    if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != ' ') return true;
	if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != ' ') return true;
	if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != ' ') return true;
	return false;
}

bool Game::row() {
	if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != ' ') return true;
	if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != ' ') return true;
	if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != ' ') return true;
	return false;
}

bool Game::diagonal() {
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return true;
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return true;
	return false;
}

bool Game::win() {
	return column() || row() || diagonal();
}

void Game::init() {
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			board[i][j] = ' ';
		}
	}
}

bool Game::draw() {
	if(win()) return false;

	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			if(board[i][j] == ' ') return false;
		}
	}
	return true;
}

void Game::show() {
    std::cout << std::endl;

	printf("\t| 0 | 1 | 2 |\t| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
	printf("\t-------------\t-------------\n");
	printf("\t| 3 | 4 | 5 |\t| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
	printf("\t-------------\t-------------\n");
	printf("\t| 6 | 7 | 8 |\t| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);

	std::cout << std::endl;
}

void Game::welcome() {
	std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;
	std::cout << title << std::endl;
}

void Game::start() {
	std::cout << "\n================================================================================================\n" << std::endl;
	std::cout << "Choose difficulty (R for Random, E for Easy, M for Medium, H for Hard): ";
	std::cin >> difficulty;

	while(difficulty != 'R' && difficulty != 'E' && difficulty != 'M' && difficulty != 'H'){
		std::cout << "Invalid difficulty! Choose difficulty (R for Random, E for Easy, M for Medium, H for Hard): ";
		std::cin >> difficulty;
	}

	switch(difficulty) {
		case 'R':
			bot = &random_bot;
			break;
		case 'E':
			bot = &easy_bot;
			break;
		case 'M':
			bot = &medium_bot;
			break;
		case 'H':
			bot = &hard_bot;
			break;
	}

	std::cout << "Choose your turn (X goes first, O follows): ";
	std::cin >> turn;

	while(turn != 'X' && turn != 'O'){
		std::cout << "Invalid turn! Choose your turn (X goes first, O follows): ";
		std::cin >> turn;
	}
	
	play();
}

void Game::play() {
	char turn = 'X';
	show();

	while(!win() && !draw()) {
		if(this->turn == turn) {
			int move;
			std::cout << "Your move: ";
			std::cin >> move;

			while(move < 0 || move > 8 || board[move / 3][move % 3] != ' ') {
				std::cout << "Invalid move! Your move: ";
				std::cin >> move;
			}

			board[move / 3][move % 3] = turn;
		}
		else {
			int move = bot->move(player(turn), board);
			std::cout << "Computer's move: " << move << std::endl;
			board[move / 3][move % 3] = turn;
		}

		show();
		turn = turn == 'X' ? 'O' : 'X';
	}

	if(win()) std::cout << (this->turn != turn ? "You" : "Computer") << " won!" << std::endl;
	else std::cout << "It's a draw!" << std::endl;

	std::cout << "Do you want to play again? (Y/N): ";
	char answer;
	std::cin >> answer;

	while(answer != 'Y' && answer != 'N'){
		std::cout << "Invalid answer! Do you want to play again? (Y/N): ";
		std::cin >> answer;
	}

	if(answer == 'Y') {
		init();
		start();
	}
}