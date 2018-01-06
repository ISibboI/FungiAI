#include "cook_mushrooms_action.hpp"
#include "game/cards/card_information.hpp"
#include "game/io/strings.hpp"

#include <sstream>

using namespace std;

CookMushroomsAction::CookMushroomsAction() :
    Action("CookMushroomsAction", 3),
    logger(spdlog::get("CookMushroomsAction")) {}

CookMushroomsAction::CookMushroomsAction(vector<uint8_t> cook_order) :
	Action("CookMushroomsAction", 3),
	cook_order(move(cook_order)),
	logger(spdlog::get("CookMushroomsAction")) {}

bool CookMushroomsAction::execute(Player& player, Forest& forest) {
	if (!player.get_display().card_count(CardInformation::pan()) > 0) {
		return false;
	}

	for (uint8_t id : cook_order) {
		if (id >= 9) {
			id -= 9;
		}

		const Card& card = CardInformation::get_card(id);

		if (!card.is_normal_mushroom()) {
			continue;
		}

		unsigned effective_card_count = player.get_hand().effective_card_count(id);

		if (effective_card_count < 3) {
			continue;
		}


		add_optimal_amount_of_ingredients(player, effective_card_count);
		player.get_display().remove_card(CardInformation::pan());
		
		unsigned card_count = player.get_hand().card_count(card);
		player.get_hand().remove_cards(card, card_count);
		player.get_display().add_cards(card, card_count);

		if (card.has_night_card()) {
			const Card& night_card = card.get_night_card();
			unsigned night_card_count = player.get_hand().card_count(night_card);
			player.get_hand().remove_cards(night_card, night_card_count);
			player.get_display().add_cards(night_card, night_card_count);
		}

		logger->debug("Cooked {:d} effective {}", effective_card_count, card.name);
		return true;
	}

	return false;
}

void CookMushroomsAction::add_optimal_amount_of_ingredients(Player& player, unsigned effective_card_count) const {
	if (effective_card_count == 8 && player.get_hand().card_count(CardInformation::butter()) >= 2) {
		effective_card_count -= 8;
		player.get_hand().remove_cards(CardInformation::butter(), 2);
		player.get_display().add_cards(CardInformation::butter(), 2);
	}

	while (effective_card_count >= 5 && player.get_hand().card_count(CardInformation::cidre()) > 0) {
		effective_card_count -= 5;
		player.get_hand().remove_card(CardInformation::cidre());
		player.get_display().add_card(CardInformation::cidre());
	}

	while (effective_card_count >= 4 && player.get_hand().card_count(CardInformation::butter()) > 0) {
		effective_card_count -= 4;
		player.get_hand().remove_card(CardInformation::butter());
		player.get_display().add_card(CardInformation::butter());
	}
}

string CookMushroomsAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name() << ":\n";
	ss << prefix << "  Cook order: " << Strings::str(cook_order);
	return ss.str();
}

vector<uint8_t>& CookMushroomsAction::get_cook_order() {
    return cook_order;
}
