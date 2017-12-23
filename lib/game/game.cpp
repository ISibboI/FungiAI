#include "game.hpp"

#include <sstream>

Game::Game() :
	p1("Player 1"),
	p2("Player 2"),
	logger(spdlog::stdout_logger_st("Game")) {}

void Game::initialize(mt19937_64& random_engine) {
	forest.initialize(random_engine);
	p1.initialize(forest);
	p2.initialize(forest);
}

void Game::post_turn_actions() {
	logger->trace("Performing post turn actions");
	forest.post_turn_actions();
	p1.post_turn_actions();
	p2.post_turn_actions();
	logger->trace("Performed post turn actions");
}

Player& Game::get_p1() {
	return p1;
}

Player& Game::get_p2() {
	return p2;
}

Forest& Game::get_forest() {
	return forest;
}

Player& Game::get_player(bool p1) {
	return p1 ? this->p1 : p2;
}

string Game::str() const {
	stringstream ss;
	ss << "Game:\n" << forest.str("  ") << "\n" << p1.str("  ") << "\n" << p2.str("  ");
	return ss.str();
}