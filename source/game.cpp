#include "game.hpp"

Game::Game() : p1(nullptr), p2(nullptr) {
	title = R"(
	 ______  __  ______       ______  ______  ______       ______  ______  ______    
	/\__  _\/\ \/\  ___\     /\__  _\/\  __ \/\  ___\     /\__  _\/\  __ \/\  ___\   
	\/_/\ \/\ \ \ \ \____    \/_/\ \/\ \  __ \ \ \____    \/_/\ \/\ \ \/\ \ \  __\   
	   \ \_\ \ \_\ \_____\      \ \_\ \ \_\ \_\ \_____\      \ \_\ \ \_____\ \_____\ 
	    \/_/  \/_/\/_____/       \/_/  \/_/\/_/\/_____/       \/_/  \/_____/\/_____/
	)";

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

Bot *Game::get_bot(char difficulty) {
	switch(difficulty) {
		case 'R': return new v0;
		case 'E': return new v1;
		case 'M': return new v2;
		case 'H': return new v3;
		default: return new v0;
	}
}

void Game::start() {
	std::cout << "\n================================================================================================\n" << std::endl;
	
	char choice;
	std::cout << "Enter P to play, S to simulate or Ctrl-C to quit: ";
	std::cin >> choice;

	while(choice != 'P' && choice != 'S'){
		std::cout << "Invalid choice! Enter P to play, S to simulate or Ctrl-C to quit: ";
		std::cin >> choice;
	}

	if(choice == 'P') play();
	else simulate();
}

void Game::play() {
	init();
	std::cout << std::endl;

	char c1;
	std::cout << "Choose difficulty for player 1 (P for Player, R for Random, E for Easy, M for Medium, H for Hard): ";
	std::cin >> c1;

	while(c1 != 'P' && c1 != 'R' && c1 != 'E' && c1 != 'M' && c1 != 'H'){
		std::cout << "Invalid difficulty! Choose difficulty (R for Random, E for Easy, M for Medium, H for Hard): ";
		std::cin >> c1;
	}

	if(c1 != 'P') {
		if(p1) delete p1;
		p1 = get_bot(c1);
	}

	char c2;
	std::cout << "Choose difficulty for player 2 (P for Player, R for Random, E for Easy, M for Medium, H for Hard): ";
	std::cin >> c2;

	while(c2 != 'P' && c2 != 'R' && c2 != 'E' && c2 != 'M' && c2 != 'H'){
		std::cout << "Invalid difficulty! Choose difficulty (R for Random, E for Easy, M for Medium, H for Hard): ";
		std::cin >> c2;
	}

	if(c2 != 'P') {
		if(p2) delete p2;
		p2 = get_bot(c2);
	}

	char turn = 'X';
	show();

	while(!win() && !draw()) {
		if(turn == 'X') {
			int move;
			std::cout << "Player 1's move: ";

			if(c1 == 'P') {
				std::cin >> move;
				while(move < 0 || move > 8 || board[move / 3][move % 3] != ' ') {
					std::cout << "Invalid move! Player 1's move:  ";
					std::cin >> move;
				}
			}
			else {
				move = p1->move(player(turn), board);
				std::cout << move << std::endl;
			}

			board[move / 3][move % 3] = turn;
		}
		else {
			int move;
			std::cout << "Player 2's move: ";

			if(c2 == 'P') {
				std::cin >> move;
				while(move < 0 || move > 8 || board[move / 3][move % 3] != ' ') {
					std::cout << "Invalid move! Player 2's move:  ";
					std::cin >> move;
				}
			}
			else {
				move = p2->move(player(turn), board);
				std::cout << move << std::endl;
			}

			board[move / 3][move % 3] = turn;
		}

		show();
		turn = turn == 'X' ? 'O' : 'X';
	}

	if(win()) std::cout << (turn != 'X' ? "Player 1" : "Player 2") << " won!" << std::endl;
	else std::cout << "It's a draw!" << std::endl;

	char choice;
	std::cout << "Do you want to play again? (Y/N): ";
	std::cin >> choice;

	while(choice != 'Y' && choice != 'N'){
		std::cout << "Invalid choice! Do you want to play again? (Y/N): ";
		std::cin >> choice;
	}

	if(choice == 'Y') play();
	else start();
}

void Game::simulate() {
	char choice;
	int rounds;

	std::cout << std::endl;
	std::cout << "Choose difficulty for player 1 (R for Random, E for Easy, M for Medium, H for Hard): ";
	std::cin >> choice;

	while(choice != 'R' && choice != 'E' && choice != 'M' && choice != 'H'){
		std::cout << "Invalid choice! Choose choice (R for Random, E for Easy, M for Medium, H for Hard): ";
		std::cin >> choice;
	}

	if(p1) delete p1;
	p1 = get_bot(choice);

	std::cout << "Choose difficulty for player 2 (R for Random, E for Easy, M for Medium, H for Hard): ";
	std::cin >> choice;

	while(choice != 'R' && choice != 'E' && choice != 'M' && choice != 'H'){
		std::cout << "Invalid choice! Choose choice (R for Random, E for Easy, M for Medium, H for Hard): ";
		std::cin >> choice;
	}

	if(p2) delete p2;
	p2 = get_bot(choice);

	std::cout << "Number of rounds: ";
	std::cin >> rounds;

	int p1_wins = 0, p2_wins = 0, draws = 0;
	int p1_pairs = 0, p2_pairs = 0, draw_pairs = 0;

	for(int i = 0; i < rounds; ++i) {
		init();
		char turn = 'X';

		int verdict = 0;

		while(!win() && !draw()) {
			int move = (turn == 'X' ? p1->move(X, board) : p2->move(O, board));
			board[move / 3][move % 3] = turn;
			turn = (turn == 'X' ? 'O' : 'X');
		}

		if(win()) {
			if(turn == 'X') ++p2_wins, --verdict;
			else ++p1_wins, ++verdict;
		}
		else ++draws;

		init();
		turn = 'X';

		while(!win() && !draw()) {
			int move = (turn == 'X' ? p2->move(X, board) : p1->move(O, board));
			board[move / 3][move % 3] = turn;
			turn = (turn == 'X' ? 'O' : 'X');
		}

		if(win()) {
			if(turn == 'X') ++verdict;
			else --verdict;
		}

		if(verdict > 0) ++p1_pairs;
		else if(verdict < 0) ++p2_pairs;
		else ++draw_pairs;
	}

	std::cout << std::fixed << std::setprecision(2) << std::endl;
	std::cout << "Player 1 wins: " << p1_wins << " with percentage of " << (p1_wins * 100.0 / rounds) << "%" << std::endl;
	std::cout << "Player 2 wins: " << p2_wins << " with percentage of " << (p2_wins * 100.0 / rounds) << "%" << std::endl;
	std::cout << "Draws: " << draws << " with percentage of " << (draws * 100.0 / rounds) << "%" << std::endl;
	std::cout << "W/D/L ratio: " << p1_wins << " / " << draws << " / " << p2_wins << std::endl;

	std::cout << std::endl;
	std::cout << "Player 1 pairs: " << p1_pairs << " with percentage of " << (p1_pairs * 100.0 / rounds) << "%" << std::endl;
	std::cout << "Player 2 pairs: " << p2_pairs << " with percentage of " << (p2_pairs * 100.0 / rounds) << "%" << std::endl;
	std::cout << "Draw pairs: " << draw_pairs << " with percentage of " << (draw_pairs * 100.0 / rounds) << "%" << std::endl;
	std::cout << "W/D/L pair ratio: " << p1_pairs << " / " << draw_pairs << " / " << p2_pairs << std::endl;

	std::cout << std::endl;
	std::cout << "Do you want to simulate again? (Y/N): ";
	std::cin >> choice;

	while(choice != 'Y' && choice != 'N'){
		std::cout << "Invalid choice! Do you want to simulate again? (Y/N): ";
		std::cin >> choice;
	}

	if(choice == 'Y') simulate();
	else start();
}