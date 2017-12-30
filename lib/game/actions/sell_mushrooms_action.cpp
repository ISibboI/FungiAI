#include "sell_mushrooms_action.hpp"
#include "game/cards/card_information.hpp"
#include "game/io/strings.hpp"

#include <sstream>

using namespace std;

SellMushroomsAction::SellMushroomsAction(vector<uint8_t>&& sell_order) :
	Action("SellMushroomsAction", 4),
	sell_order(move(sell_order)),
	logger(spdlog::get("SellMushroomsAction")) {}

SellMushroomsAction::~SellMushroomsAction() {}

bool SellMushroomsAction::execute(Player& player, Forest& forest) {
	for (uint8_t id : sell_order) {
		unsigned effective_card_count = player.get_hand().effective_card_count(id);

		if (effective_card_count < 2) {
			continue;
		}

		const Card& card = CardInformation::get_card(id);
		
		unsigned card_count = player.get_hand().card_count(card);
		player.get_hand().remove_cards(card, card_count);
		forest.get_discard_pile().add_cards(card, card_count);

		if (card.has_night_card()) {
			const Card& night_card = card.get_night_card();
			unsigned night_card_count = player.get_hand().card_count(night_card);
			player.get_hand().remove_cards(night_card, night_card_count);
			forest.get_discard_pile().add_cards(night_card, night_card_count);
		}

		player.get_display().add_cards(CardInformation::stick(), effective_card_count * card.price);

		logger->debug("Selled {:d} effective {}", effective_card_count, card.name);
		return true;
	}

	return false;
}

string SellMushroomsAction::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << get_name() << ":\n";
	ss << prefix << "  Sell order: " << Strings::str(sell_order);
	return ss.str();
}