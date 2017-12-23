#include "place_pan_action.hpp"
#include "game/cards/card_information.hpp"

#include <sstream>

using namespace std;

PlacePanAction::PlacePanAction() :
	Action("PlacePanAction", 5),
	logger(spdlog::get("PlacePanAction")) {}

PlacePanAction::~PlacePanAction() {}

bool PlacePanAction::execute(Player& player, Forest& forest) const {
	if (player.get_hand().card_count(CardInformation::pan()) > 0) {
		player.get_hand().remove_card(CardInformation::pan());
		player.get_display().add_card(CardInformation::pan());
		logger->debug("Placed pan");
		return true;
	}

	return false;
}

string PlacePanAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name();
	return ss.str();
}