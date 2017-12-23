#include "action.hpp"

using namespace std;

Action::Action(const string& name, unsigned id) : name(name), id(id) {}

Action::~Action() {}

const string& Action::get_name() const {
	return name;
}

unsigned Action::get_id() const {
	return id;
}

string Action::str() const {
	return str("");
}