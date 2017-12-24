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
	virtual ~Controller();

	virtual void do_turn(Player& me, Player& enemy, Forest& forest) = 0;
	void do_turn(Game& game, bool p1);

	const string& get_name() const;
};

#endif