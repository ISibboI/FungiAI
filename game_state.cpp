#include "game_state.h"
#include "debug.h"

#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

GameState::GameState(mt19937& r) : draw_pile("Draw pile", sizeof(initial_draw_pile)), forest("Forest", 8), decay_pile("Decay pile", 4),
    discard_pile("Discard pile"), display_p1("Display p1"), display_p2("Display p2"), hand_p1("Hand p1"), hand_p2("Hand p2") {

    draw_pile.add_cards(initial_draw_pile, sizeof(initial_draw_pile));
    shuffle(draw_pile.get_offset(), draw_pile.get_limit(), r);
    print_array("draw_pile", draw_pile.get_offset(), draw_pile.size());

    forest.make_space(8);
    draw_pile.remove_cards(draw_pile.size() - 8, 8, forest.get_offset());

    display_p1.add_card(pan);
    display_p2.add_card(pan);

    for (int i = 0; i < 3; i++) {
        draw_initial_card(display_p1, hand_p1);
        draw_initial_card(display_p2, hand_p2);
    }
}

GameState::~GameState() {}

bool GameState::check_general_pickup(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand, StructuredPile* picked_cards) {
    uint8_t drop_size = 0;
    int8_t pick_all_size = picked_cards->pick_all_size();
    int8_t remaining_capacity = hand->get_remaining_capacity(*display);

    if (pick_all_size > remaining_capacity) {
        return false;
    }

    if ((*picked_cards)[fly_agaric] > 0 && display->get_count(fly_agaric) == 0) {
        drop_size = (uint8_t) max(0, 4 - remaining_capacity + pick_all_size);

        for (unsigned i = 0; i < special_min_id; i++) {
            if (drop_ids->get_count(i) > hand->get_count(i) + (*picked_cards)[i]) {
                return false;
            }
        }

        for (unsigned i = special_min_id; i < cards_size; i++) {
            if (drop_ids->get_count(i) > 0) {
                throw runtime_error("Can't drop cards that never go into the hand");
            }
        }
    }

    return drop_ids->size() == drop_size;
}

bool GameState::check_action_pick(uint8_t index, StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    if (index >= forest.size()) {
        return false;
    }

    uint8_t card = forest[index];
    uint8_t price = max(0, index - 1);
    StructuredPile pick_pile("Pick pile");
    pick_pile.add_card(card);

    return price <= display->get_count(stick) && check_general_pickup(drop_ids, display, hand, &pick_pile);
}

bool GameState::check_action_decay(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    StructuredPile* structured_decay_pile = decay_pile.structurize();
    bool result = check_general_pickup(drop_ids, display, hand, structured_decay_pile);
    delete structured_decay_pile;

    return result;
}

bool GameState::check_action_cook(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    return display->get_count(pan) > 0 && count >= 3 && hand->get_effective_shroom_count(id) >= count;
}

bool GameState::check_action_sell(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    return count >= 2 && hand->get_effective_shroom_count(id) >= count;
}

bool GameState::check_action_pan(StructuredPile* display, HandStructuredPile* hand) {
    return hand->get_count(pan) > 0;
}

bool GameState::check_action_pass(StructuredPile* display, HandStructuredPile* hand) {
    int8_t capacity = hand->get_remaining_capacity(*display);
    uint8_t forest_limit = min(forest.size(), (uint8_t) (2 + display->get_count(stick)));

    // Pick
    for (unsigned i = 0; i < forest_limit; i++) {
        if (cards[forest[i]].size <= capacity) {
            return false;
        }
    }

    // Decay
    if (decay_pile.pick_all_size() <= capacity) {
        return false;
    }

    // Cook & Sell
    for (unsigned i = 0; i < night_min_id; i++) {
        if (hand->get_count(i) >= 2) {
            return false;
        }
    }

    if (hand->get_night_card_count() > 0) {
        return false;
    }

    // Pan
    if (check_action_pan(display, hand)) {
        return false;
    }

    return true;
}

bool GameState::action_pick(uint8_t index, StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::action_decay(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::action_cook(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::action_sell(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::action_pan(StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::action_pass(StructuredPile* display, HandStructuredPile* hand) {
    // TODO
    return false;
}

bool GameState::finalize_turn(bool p1) {
    print("Entering finalize turn");

    if (forest.size() <= 1) {
        print("Game end detected");
        return false;
    }

    if (decay_pile.is_full()) {
        print("Decay pile is full");

        while (decay_pile.size() > 0) {
            discard_pile.add_card(decay_pile.remove_last_card());
        }

        decay_pile.clear();
    }

    print_var(forest[0]);

    decay_pile.add_card(forest.remove_card(0));

    while (forest.size() < 8 && draw_pile.size() > 0) {
        forest.add_card(draw_pile.remove_last_card());
    }

    if (p1) {
        if (display_p1[fly_agaric] > 0) {
            display_p1.remove_card(fly_agaric);

            if (display_p1[fly_agaric] == 0) {
                discard_pile.add_card(fly_agaric);
            }
        }
    } else {
        if (display_p2[fly_agaric] > 0) {
            display_p2.remove_card(fly_agaric);

            if (display_p2[fly_agaric] == 0) {
                discard_pile.add_card(fly_agaric);
            }
        }
    }

    print("Exiting finalize turn without ending game");
    return true;
}

void GameState::get_p1_view(uint8_t& draw_pile_size, StructuredPile*& discard_pile,
    Pile*& forest, Pile*& decay_pile,
    StructuredPile*& display, HandStructuredPile*& hand,
    StructuredPile*& opponent_display, HandStructuredPile*& opponent_hand) {

    draw_pile_size = draw_pile.size();
    discard_pile = &this->discard_pile;
    forest = &this->forest;
    decay_pile = &this->decay_pile;
    display = &display_p1;
    hand = &hand_p1;
    opponent_display = &display_p2;
    opponent_hand = &hand_p2;
}

void GameState::get_p2_view(uint8_t& draw_pile_size, StructuredPile*& discard_pile,
    Pile*& forest, Pile*& decay_pile,
    StructuredPile*& display, HandStructuredPile*& hand,
    StructuredPile*& opponent_display, HandStructuredPile*& opponent_hand) {

    draw_pile_size = draw_pile.size();
    discard_pile = &this->discard_pile;
    forest = &this->forest;
    decay_pile = &this->decay_pile;
    display = &display_p2;
    hand = &hand_p2;
    opponent_display = &display_p1;
    opponent_hand = &hand_p1;
}

string GameState::str() {
    stringstream ss;

    ss << hand_p1.str() << "\n";
    ss << display_p1.str() << "\n";
    ss << forest.str() << "\n";
    ss << decay_pile.str() << "\n";
    ss << display_p2.str() << "\n";
    ss << hand_p2.str() << "\n";
    ss << discard_pile.str();

    return ss.str();
}

inline void GameState::draw_initial_card(StructuredPile& display, HandStructuredPile& hand) {
    uint8_t card = draw_pile.remove_last_card();

    // Baskets directly go into the display
    if (card == basket) {
        display_p1.add_card(basket);
    } else if (card == fly_agaric) {
        // Fly agarics go directly into the discard_pile
        discard_pile.add_card(fly_agaric);
    } else {
        // Everything else goes into the players hand
        hand.add_card(card);
    }
}
