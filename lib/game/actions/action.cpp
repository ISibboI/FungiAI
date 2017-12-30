#include "action.hpp"

using namespace std;

Action::Action(const string& name, unsigned id) : name(name), id(id), action_result(0) {}

Action::~Action() {
	if (action_result != 0) {
		delete action_result;
	}
}

const string& Action::get_name() const {
	return name;
}

unsigned Action::get_id() const {
	return id;
}

void Action::set_result(ActionResult* action_result) {
	this->action_result = action_result;
}

const ActionResult* Action::get_result() const {
	return action_result;
}

string Action::str() const {
	return str("");
}