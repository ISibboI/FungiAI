#include "controller.hpp"

Controller::Controller(const string& name) :
	name(name) {}

void Controller::do_turn(Game& game, bool p1) {
	do_turn(game.get_player(p1), game.get_player(!p1), game.get_forest());
}

const string& Controller::get_name() const {
	return name;
}