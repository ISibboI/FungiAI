#include "NNCoder.hpp"

#include <numeric>

size_t NNCoder::nn_input_size = (size_t) -1;

void NNCoder::encode(unsigned i, unsigned max_value, float** output) {
    for (unsigned counter = 0; counter < i; counter++) {
        *((*output)++) = 0.f;
    }

    *((*output)++) = 1.f;

    for (unsigned counter = 0; counter < max_value - i; counter++) {
        *((*output)++) = 0.f;
    }
}

void NNCoder::encode(vector<uint8_t>& ids, unsigned size, float** output) {
	unsigned count = 0;

	for (uint8_t id : ids) {
		count++;

		// Use stick as invalid
		encode(id, CardInformation::get_all_cards().size() - 1, output);
	}

    assert(count <= size);

	for (; count < size; count++) {
		encode(CardInformation::get_all_cards().size() - 1, CardInformation::get_all_cards().size() - 1, output);
	}
}

void NNCoder::encode(StructuredPile& structured_pile, bool hidden, float** output) {
	unsigned night_card_count = 0;

	for (uint8_t id = 0; id < 22; id++) {
		const Card& card = CardInformation::get_card(id);

		if (card.is_night_card() && hidden) {
			night_card_count++;
			encode(0, card.ingame_amount, output);
		} else {
			encode(structured_pile.card_count(card), card.ingame_amount, output);
		}
	}

	if (hidden) {
		encode(night_card_count, 8, output);
	}
}

void NNCoder::encode(Forest& forest, float** output) {
	encode(forest.get_draw_pile().size(), CardInformation::initial_draw_pile_size(), output);
	encode(forest.get_forest(), 8, output);
    encode(forest.get_forest().size(), 8, output);
	encode(forest.get_decay_pile(), 4, output);
    encode(forest.get_decay_pile().size(), 4, output);
	encode(forest.get_discard_pile(), false, output);
}

void NNCoder::encode(Player& player, bool hidden, float** output) {
	encode(player.get_display(), false, output);
	encode(player.get_hand(), hidden, output);
}

void NNCoder::encode(Game& game, bool p1, float* nn_input) {
	encode(game.get_forest(), &nn_input);
	encode(game.get_player(p1), false, &nn_input);
	encode(game.get_player(!p1), true, &nn_input);
}

void NNCoder::decode_priority_permutation(float** begin, unsigned length, vector<uint8_t>& output) {
    output.resize(length);
    std::iota(output.begin(), output.end(), 0);

    std::sort(output.begin(), output.end(), [begin](const uint8_t& a, const uint8_t& b) -> bool {
        // Decode highest priority first
        return *(*begin + a) > *(*begin + b);
    });

    *begin += length;
}

void NNCoder::decode(float* nn_output, CombinedAction& output) {
    decode_priority_permutation(&nn_output, 5, output.get_action_order());
    decode_priority_permutation(&nn_output, 8, output.get_pick_order());
    decode_priority_permutation(&nn_output, 20, output.get_discard_order());
    decode_priority_permutation(&nn_output, 9, output.get_cook_order());
    decode_priority_permutation(&nn_output, 9, output.get_sell_order());
}
