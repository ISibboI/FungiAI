#include "discard_action.hpp"
#include "game/cards/card_information.hpp"
#include "game/io/strings.hpp"

#include <sstream>

using namespace std;

DiscardAction::DiscardAction() :
	Action("DiscardAction", 0),
	logger(spdlog::get("DiscardAction")) {}

DiscardAction::DiscardAction(const string& name, unsigned id) :
	Action(name, id) {}

DiscardAction::DiscardAction(vector<uint8_t>&& discard_order) :
	Action("DiscardAction", 0),
	discard_order(discard_order),
	logger(spdlog::get("DiscardAction")) {}

DiscardAction::DiscardAction(DiscardAction&& discard_action) :
	Action("DiscardAction", 0),
	discard_order(move(discard_action.discard_order)),
	logger(spdlog::get("DiscardAction")) {}

DiscardAction::~DiscardAction() {}

bool DiscardAction::execute(Player& player, Forest& forest) {
	unsigned current_index = 0;
	Hand& hand = player.get_hand();

	while (hand.size() > player.get_hand_capacity()) {
		while (current_index < discard_order.size() && hand.card_count(discard_order[current_index]) == 0) {
			current_index++;
		}

		if (hand.card_count(discard_order[current_index]) == 0) {
			return false;
		}

		hand.remove_card(discard_order[current_index]);
		forest.get_discard_pile().add_card(discard_order[current_index]);
		logger->debug("Discarded {}", CardInformation::get_card(discard_order[current_index]).name);
	}

	return true;
}

string DiscardAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name() << ":\n";
	ss << prefix << "  Discard order: " << Strings::str(discard_order);
	return ss.str();
}