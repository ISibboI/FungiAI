#ifndef CARD_INFORMATION_HPP
#define CARD_INFORMATION_HPP

#include "card.hpp"

#include <vector>
#include <string>

using namespace std;

const vector<Card> all_cards{
		Card("Honey fungus", 1, 1, 1, 10, 0),
		Card("Tree Ear", 1, 2, 1, 8, 1),
		Card("Lawyer's Wig", 2, 1, 1, 6, 2),
		Card("Shiitake", 2, 2, 1, 5, 3),
		Card("Hen of the Woods", 3, 1, 1, 5, 4),
		Card("Birch bolete", 3, 2, 1, 4, 5),
		Card("Porcini", 3, 3, 1, 4, 6),
		Card("Chanterelle", 4, 2, 1, 4, 7),
		Card("Morels", 6, 4, 1, 3, 8),
		Card("Night Honey fungus", 2, 2, 1, 1, 9),
		Card("Night Tree Ear", 2, 4, 1, 1, 10),
		Card("Night Lawyer's Wig", 4, 2, 1, 1, 11),
		Card("Night Shiitake", 4, 4, 1, 1, 12),
		Card("Night Hen of the Woods", 6, 2, 1, 1, 13),
		Card("Night Birch bolete", 6, 4, 1, 1, 14),
		Card("Night Porcini", 6, 6, 1, 1, 15),
		Card("Night Chanterelle", 8, 4, 1, 1, 16),
		Card("Butter", 3, 4, 1, 3, 17),
		Card("Cidre", 5, 5, 1, 3, 18),
		Card("Pan", -1, -1, 1, 13, 11, 19),
		Card("Basket", -1, -1, -2, 5, 20),
		Card("Fly agaric", -1, -1, 0, 5, 21),
		Card("Moon", -1, -1, 0, 0, 22),
		Card("Stick", -1, 1, 0, 200, 23)
	};

class CardInformation {
private:

public:
	static const vector<Card>& get_all_cards() {
		return all_cards;
	}

	static const Card& get_card(uint8_t id) {
		return all_cards[id];
	}

	static vector<uint8_t> create_initial_draw_pile() {
		vector<uint8_t> initial_draw_pile;

		for (uint8_t id = 0; id < 22; id++) {
			initial_draw_pile.insert(initial_draw_pile.end(), all_cards[id].draw_pile_amount, id);
		}

		return initial_draw_pile;
	}

	static const unsigned initial_draw_pile_size() {
		unsigned count = 0;

		for (const Card& card : all_cards) {
			count += card.draw_pile_amount;
		}

		return count;
	}

	static const Card& honey_fungus() {
		return all_cards[0];
	}

	static const Card& tree_ear() {
		return all_cards[1];
	}

	static const Card& lawyers_wig() {
		return all_cards[2];
	}

	static const Card& shiitake() {
		return all_cards[3];
	}

	static const Card& hen_of_the_woods() {
		return all_cards[4];
	}

	static const Card& birch_bolete() {
		return all_cards[5];
	}

	static const Card& porcini() {
		return all_cards[6];
	}

	static const Card& chanterelle() {
		return all_cards[7];
	}

	static const Card& morels() {
		return all_cards[8];
	}

	static const Card& night_honey_fungus() {
		return all_cards[9];
	}

	static const Card& night_tree_ear() {
		return all_cards[10];
	}

	static const Card& night_lawyers_wig() {
		return all_cards[11];
	}

	static const Card& night_shiitake() {
		return all_cards[12];
	}

	static const Card& night_hen_of_the_woods() {
		return all_cards[13];
	}

	static const Card& night_birch_bolete() {
		return all_cards[14];
	}

	static const Card& night_porcini() {
		return all_cards[15];
	}

	static const Card& night_chanterelle() {
		return all_cards[16];
	}

	static const Card& butter() {
		return all_cards[17];
	}

	static const Card& cidre() {
		return all_cards[18];
	}

	static const Card& pan() {
		return all_cards[19];
	}

	static const Card& basket() {
		return all_cards[20];
	}

	static const Card& fly_agaric() {
		return all_cards[21];
	}

	static const Card& moon() {
		return all_cards[22];
	}

	static const Card& stick() {
		return all_cards[23];
	}
};

#endif