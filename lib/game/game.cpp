#include "game.hpp"

#include <sstream>

Game::Game() :
	p1("Player 1"),
	p2("Player 2") {}

void Game::initialize(mt19937_64& random_engine) {
	forest.initialize(random_engine);
	p1.initialize(forest);
	p2.initialize(forest);
}

string Game::str() const {
	stringstream ss;
	ss << "Game:\n" << forest.str("  ") << "\n" << p1.str("  ") << "\n" << p2.str("  ");
	return ss.str();
}