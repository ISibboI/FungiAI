#ifndef GAME_HPP
#define GAME_HPP

#include "data/player.hpp"
#include "data/forest.hpp"

class Game {
private:
	Player p1;
	Player p2;
	Forest forest;

public:
	Game();
};

#endif