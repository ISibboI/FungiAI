#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "game/game.hpp"

#include <string>

using namespace std;

class Controller {
private:
	string name;

public:
	Controller(const string& name);
	~Controller();

	virtual void do_turn(Game& game, bool p1) = 0;
};

#endif