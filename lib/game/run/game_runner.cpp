#include "game_runner.hpp"

GameRunner::GameRunner() {}

GameRunner::~GameRunner() {}

bool GameRunner::run_game(Controller* p1, Controller* p2, mt19937_64& random_engine) {
	game.initialize(random_engine);
	bool turn_p1 = true;

	while (!game.is_finished()) {
		Controller* player = turn_p1 ? p1 : p2;

		player->do_turn(game, turn_p1);
		turn_p1 = !turn_p1;
	}

	return game.winner();
}