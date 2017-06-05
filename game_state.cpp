#include "game_state.h"
#include "debug.h"

#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

GameState::GameState(mt19937& r) : draw_pile("Draw pile", sizeof(initial_draw_pile)), forest("Forest", 8), decay_pile("Decay pile", 4) {
    draw_pile.add_cards(initial_draw_pile, sizeof(initial_draw_pile));
    shuffle(draw_pile.get_offset(), draw_pile.get_limit(), r);
    print_array("draw_pile", draw_pile.get_offset(), draw_pile.size());

    forest.make_space(8);
    draw_pile.remove_cards(draw_pile.size() - 8, 8, forest.get_offset());

    memset(discard_pile, 0, sizeof(discard_pile) * sizeof(uint8_t));
    memset(display_p1, 0, sizeof(display_p1) * sizeof(uint8_t));
    memset(display_p2, 0, sizeof(display_p2) * sizeof(uint8_t));
    memset(hand_p1, 0, sizeof(hand_p1) * sizeof(uint8_t));
    memset(hand_p2, 0, sizeof(hand_p2) * sizeof(uint8_t));

    display_p1[pan] = 1;
    display_p2[pan] = 1;

    for (int i = 0; i < 3; i++) {
        draw_initial_card(display_p1, hand_p1);
        draw_initial_card(display_p2, hand_p2);
    }
}

GameState::~GameState() {}

bool GameState::action_pick(uint8_t index, uint8_t* drop_ids, uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_decay(uint8_t* drop_ids, uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_cook(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_sell(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_pan(uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_pass(uint8_t* display, uint8_t* hand) {
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
        // TODO Add decay pile to discard pile
        
        decay_pile.clear();
    }

    print_var(forest[0]);

    decay_pile.add_card(forest.remove_card(0));

    while (forest.size() < 8 && draw_pile.size() > 0) {
        forest.add_card(draw_pile.remove_last_card());
    }

    if (p1) {
        if (display_p1[fly_agaric] > 0) {
            display_p1[fly_agaric]--;

            if (display_p1[fly_agaric] == 0) {
                discard_pile[fly_agaric]++;
            }
        }
    } else {
        if (display_p2[fly_agaric] > 0) {
            display_p2[fly_agaric]--;

            if (display_p2[fly_agaric] == 0) {
                discard_pile[fly_agaric]++;
            }
        }
    }

    print("Exiting finalize turn without ending game");
    return true;
}

void GameState::get_p1_view(uint8_t& draw_pile_size, uint8_t*& discard_pile,
    Pile*& forest, Pile*& decay_pile,
    uint8_t*& display, uint8_t*& hand,
    uint8_t*& opponent_display, uint8_t*& opponent_hand) {

    draw_pile_size = draw_pile.size();
    discard_pile = this->discard_pile;
    forest = &this->forest;
    decay_pile = &this->decay_pile;
    display = display_p1;
    hand = hand_p1;
    opponent_display = display_p2;
    opponent_hand = hand_p2;
}

void GameState::get_p2_view(uint8_t& draw_pile_size, uint8_t*& discard_pile,
    Pile*& forest, Pile*& decay_pile,
    uint8_t*& display, uint8_t*& hand,
    uint8_t*& opponent_display, uint8_t*& opponent_hand) {

    draw_pile_size = draw_pile.size();
    discard_pile = this->discard_pile;
    forest = &this->forest;
    decay_pile = &this->decay_pile;
    display = display_p2;
    hand = hand_p2;
    opponent_display = display_p1;
    opponent_hand = hand_p1;
}

string GameState::str() {
    stringstream ss;

    ss << "Hand p1: ";

    for (unsigned i = 0; i < sizeof(hand_p1) - 2; i++) {
        if (hand_p1[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) hand_p1[i] << "; ";
        }
    }

    ss << "size: " << (unsigned) hand_p1[hand_size];
    ss << "; night_card_count: " << (unsigned) hand_p1[night_card_count];

    ss << "\nDisplay p1: ";

    for (unsigned i = 0; i < sizeof(display_p1); i++) {
        if (display_p1[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) display_p1[i] << "; ";
        }
    }

    ss << "\nForest: ";

    for (unsigned i = 0; i < forest.size(); i++) {
        ss << cards[forest[i]].str() << "; ";
    }

    #ifdef DEBUG
    print_var(decay_pile.size());
    #endif

    ss << "\nDecay pile: ";

    for (uint8_t* i = decay_pile.get_offset(); i < decay_pile.get_limit(); i++) {
        ss << cards[*i].str() << "; ";
    }

    ss << "\nDisplay p2: ";

    for (unsigned i = 0; i < sizeof(display_p2); i++) {
        if (display_p2[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) display_p2[i] << "; ";
        }
    }

    ss << "\nHand p2: ";

    for (unsigned i = 0; i < sizeof(hand_p2) - 2; i++) {
        if (hand_p2[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) hand_p2[i] << "; ";
        }
    }

    ss << "size: " << (unsigned) hand_p2[hand_size];
    ss << "; night_card_count: " << (unsigned) hand_p2[night_card_count];

    ss << "\nDiscard pile: ";

    for (unsigned i = 0; i < sizeof(discard_pile); i++) {
        if (discard_pile[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) discard_pile[i] << "; ";
        }
    }

    return ss.str();
}

inline void GameState::draw_initial_card(uint8_t* display, uint8_t* hand) {
    uint8_t card = draw_pile.remove_last_card();

    // Baskets directly go into the display
    if (card == basket) {
        display_p1[basket]++;
    } else if (card == fly_agaric) {
        // Fly agarics go directly into the discard_pile
        discard_pile[fly_agaric]++;
    } else {
        // Everything else goes into the players hand
        hand[card]++;
        hand[hand_size]++;

        if (card >= night_min_id && card <= night_max_id) {
            hand[night_card_count]++;
        }
    }
}
