#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "forest.hpp"
#include "spdlog.h"

#include <memory>

class Game {
private:
	Player p1;
	Player p2;
	Forest forest;
	shared_ptr<spdlog::logger> logger;

public:
	Game();

	void initialize(mt19937_64& random_engine);

	void post_turn_actions();

	Player& get_p1();
	Player& get_p2();
	Forest& get_forest();
	Player& get_player(bool p1);

	bool is_finished() const;
	bool winner() const;

	string str() const;
};

#endif