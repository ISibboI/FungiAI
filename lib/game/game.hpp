#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "forest.hpp"

class Game {
private:
	Player p1;
	Player p2;
	Forest forest;

public:
	Game();
};

#endif