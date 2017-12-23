#include "pick_action.hpp"
#include "game/cards/card_information.hpp"
#include "io/strings.hpp"

#include <sstream>

using namespace std;

PickAction::PickAction(vector<uint8_t>&& pick_order, DiscardAction&& discard_action) :
	Action("PickAction", 1),
	pick_order(pick_order),
	discard_action(move(discard_action)) {}

PickAction::~PickAction() {}

bool PickAction::execute(Player& player, Forest& forest) const {
	for (const uint8_t index : pick_order) {
		const uint8_t costs = index == 0 ? 0 : index - 1;

		// Do we have enough money?
		if (player.get_display().card_count(CardInformation::stick()) < costs) {
			continue;
		}

		// Is the forest big enough?
		if (forest.get_forest().size() <= index) {
			continue;
		}

		const Card& card = CardInformation::get_card(forest.get_forest()[index]);
		forest.get_forest().erase(forest.get_forest().begin() + index);

		if (card.is_valid_hand_card()) {
			if (player.get_hand().size() >= player.get_hand_capacity()) {
				continue;
			}

			player.get_hand().add_card(card);
		} else if (card == CardInformation::basket()) {
			player.get_display().add_card(card);
		} else if (card == CardInformation::fly_agaric()) {
			forest.get_discard_pile().add_card(card);
			discard_action.execute(player, forest);
		}

		return true;
	}

	return false;
}

string PickAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name() << ":\n";
	ss << prefix << "  Pick order: " << Strings::str(pick_order);
	return ss.str();
}