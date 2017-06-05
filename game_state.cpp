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

bool GameState::action_pick(uint8_t index, StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    return false;
}

bool GameState::action_decay(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    return false;
}

bool GameState::action_cook(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    return false;
}

bool GameState::action_sell(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    return false;
}

bool GameState::action_pan(StructuredPile* display, HandStructuredPile* hand) {
    return false;
}

bool GameState::action_pass(StructuredPile* display, HandStructuredPile* hand) {
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
