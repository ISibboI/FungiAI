#include "game_runner.hpp"

GameRunner::GameRunner(Controller* p1, Controller* p2) :
	p1(p1), p2(p2) {}

GameRunner::~GameRunner() {}

bool GameRunner::run_game() {
	game.initialize(random_engine);
	bool p1 = true;

	while (!game.is_finished()) {
		Controller* player = p1 ? this->p1 : p2;

		player->do_turn(game, p1);
	}

	return game.winner();
}