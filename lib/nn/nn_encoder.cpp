#include "nn_encoder.hpp"
#include "game/cards/card_information.hpp"

NNEncoder::NNEncoder() {}

NNEncoder::~NNEncoder() {}

void NNEncoder::encode(unsigned i, unsigned max_value, vector<float>& v) {
	v.insert(v.end(), i, 0.f);
	v.push_back(1.f);
	v.insert(v.end(), max_value - i, 0.f);
}

void NNEncoder::encode(vector<uint8_t>& ids, unsigned size, vector<float>& v) {
	unsigned count = 0;

	for (uint8_t id : ids) {
		count++;

		// Use stick as invalid
		encode(id, CardInformation::get_all_cards().size() - 1, v);
	}

	for (; count < size; count++) {
		encode(CardInformation::get_all_cards().size() - 1, CardInformation::get_all_cards().size() - 1, v);
	}
}

void NNEncoder::encode(StructuredPile& structured_pile, bool hidden, vector<float>& v) {
	unsigned night_card_count = 0;

	for (uint8_t id = 0; id < 22; id++) {
		const Card& card = CardInformation::get_card(id);

		if (card.is_night_card() && hidden) {
			night_card_count++;
			encode(0, card.ingame_amount, v);
		} else {
			encode(structured_pile.card_count(card), card.ingame_amount, v);
		}
	}

	if (hidden) {
		encode(night_card_count, 8, v);
	}
}

void NNEncoder::encode(Forest& forest, vector<float>& v) {
	encode(forest.get_draw_pile().size(), CardInformation::initial_draw_pile_size(), v);
	encode(forest.get_forest(), 8, v);
	encode(forest.get_decay_pile(), 4, v);
	encode(forest.get_discard_pile(), false, v);
}

void NNEncoder::encode(Player& player, bool hidden, vector<float>& v) {
	encode(player.get_display(), false, v);
	encode(player.get_hand(), hidden, v);
}

void NNEncoder::encode(Game& game, bool p1, vector<float>& v) {
	encode(game.get_forest(), v);
	encode(game.get_player(p1), false, v);
	encode(game.get_player(!p1), true, v);
}