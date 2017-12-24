#ifndef GAME_RUNNER_HPP
#define GAME_RUNNER_HPP

#include "game/game.hpp"
#include "controller.hpp"

#include <random>

using namespace std;

class GameRunner {
private:
	mt19937_64 random_engine;
	Game game;
	Controller* p1;
	Controller* p2;

public:
	GameRunner(Controller* p1, Controller* p2);
	~GameRunner();

	bool run_game();
};

#endif