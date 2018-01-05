#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "game/game.hpp"
//#include "action_listener.hpp"

#include <string>
#include <vector>

using namespace std;

class Controller {
private:
	string name;
	//vector<ActionListener*> actionListeners;

protected:
	virtual void do_turn(Player& me, Player& enemy, Forest& forest) = 0;

public:
	explicit Controller(const string& name);
    Controller() = default;
	virtual ~Controller() = default;

	void do_turn(Game& game, bool p1);

	const string& get_name() const;
};

#endif