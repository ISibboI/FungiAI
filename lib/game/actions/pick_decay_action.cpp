#include "pick_decay_action.hpp"
#include "game/cards/card_information.hpp"
#include "io/strings.hpp"

#include <sstream>

using namespace std;

PickDecayAction::PickDecayAction(DiscardAction* discard_action) :
	Action("PickDecayAction", 2),
	discard_action(discard_action),
	logger(spdlog::get("PickDecayAction")) {}

PickDecayAction::~PickDecayAction() {}

bool PickDecayAction::execute(Player& player, Forest& forest) {
	int current_capacity = player.get_hand_capacity() - player.get_hand().size();
	int decay_size = 0;

	for (uint8_t id : forest.get_decay_pile()) {
		decay_size += CardInformation::get_card(id).size;
	}

	if (decay_size > current_capacity || forest.get_decay_pile().size() == 0) {
		return false;
	}

	bool contains_fly_agaric = false;

	for (uint8_t id : forest.get_decay_pile()) {
		const Card& card = CardInformation::get_card(id);

		if (card.is_valid_hand_card()) {
			player.get_hand().add_card(id);
		} else if (card == CardInformation::basket()) {
			player.get_display().add_card(card);
		} else if (card == CardInformation::fly_agaric()) {
			forest.get_discard_pile().add_card(card);
			contains_fly_agaric = true;
		}
	}

	forest.get_decay_pile().clear();
	logger->debug("Picked decay pile");

	if (contains_fly_agaric) {
		player.set_fly_agaric_timer();
		discard_action->execute(player, forest);
	}

	return true;
}

string PickDecayAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name();
	return ss.str();
}