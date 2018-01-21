#ifndef GAME_RUNNER_HPP
#define GAME_RUNNER_HPP

#include "game/game.hpp"
#include "controller.hpp"

#include <random>

using namespace std;

class GameRunner {
private:
	Game game;

public:
	GameRunner() = default;
	~GameRunner() = default;

	bool run_game(Controller* p1, Controller* p2, mt19937_64& random_engine);
};

#endif