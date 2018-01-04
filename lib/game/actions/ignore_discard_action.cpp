#include "ignore_discard_action.hpp"
#include "game/io/strings.hpp"

#include <algorithm>
#include <sstream>

using namespace std;

IgnoreDiscardAction::IgnoreDiscardAction() : DiscardAction("IgnoreDiscardAction", 0), discard_count(0) {}

IgnoreDiscardAction::~IgnoreDiscardAction() {}

bool IgnoreDiscardAction::execute(Player& player, Forest& forest) {
	discard_count = (unsigned) max(0, (int) player.get_hand().size() - (int) player.get_hand_capacity());
}

string IgnoreDiscardAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name() << ":\n";
	ss << prefix << "  Discard count: " << discard_count;
	return ss.str();
}

unsigned IgnoreDiscardAction::get_discard_count() {
	return discard_count;
}