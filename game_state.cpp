#include "game_state.h"
#include "debug.h"

#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

GameState::GameState(mt19937& r) : decay_pile("Decay pile", 4) {
    memcpy(draw_pile, initial_draw_pile, sizeof(initial_draw_pile) * sizeof(uint8_t));
    shuffle(draw_pile, draw_pile + sizeof(draw_pile) * sizeof(uint8_t), r);
    print_array("draw_pile", draw_pile, sizeof(draw_pile));

    draw_pointer = sizeof(draw_pile) - 8;

    memcpy(forest, draw_pile + draw_pointer, 8 * sizeof(uint8_t));

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

    forest_pointer = 8;
}

GameState::~GameState() {}

bool GameState::action_pick(uint8_t index, uint8_t* drop_ids, uint8_t* display, uint8_t* hand) {
    print("Entering pick");

    if (forest[index] == fly_agaric) {
        print("Special case: Picking a fly agaric");

        uint8_t costs = max(index - 2, 0);

        if (costs > display[stick]) {
            print("Cannot pick: Not enough sticks");
            return false;
        }

        // Ensure the drop_ids have the right size
        unsigned drop_size = max(0, hand[hand_size] - 4 - display[basket]);
        unsigned drop_ids_size = 0;

        for (; drop_ids[drop_ids_size] != n1; drop_ids_size++);

        if (drop_size != drop_ids_size) {
            print("Cannot pick: Drop ids have wrong size");
            return false;
        }

        display[stick] -= costs;
        remove_forest_card(index);

        if (display[fly_agaric] > 0) {
            discard_pile[fly_agaric]++;
        }

        display[fly_agaric] = 2;

        for (; hand[hand_size] > 4 + display[basket]; hand[hand_size]--) {
            uint8_t card = *(drop_ids++);

            if (hand[card] <= 0 || card == n1) {
                throw runtime_error("Drop ids have the wrong size. This should have been checked before");
            }

            hand[card]--;

            if (card >= night_min_id && card <= night_min_id) {
                hand[night_card_count]--;
            }
        }

        if (*drop_ids != n1) {
            throw runtime_error("Drop ids have the wrong size. This should have been checked before");
        }

        print("Picked successfully");
        return true;
    }

    if (hand[hand_size] >= 8 + display[basket] - (display[fly_agaric] > 0 ? 4 : 0)) {
        print("Cannot pick: Not enough space in hand");
        return false;
    }

    uint8_t costs = max(index - 2, 0);

    if (costs > display[stick]) {
        print("Cannot pick: Not enough sticks");
        return false;
    }

    display[stick] -= costs;
    uint8_t card = forest[index];
    remove_forest_card(index);

    if (card == basket) {
        display[basket] += 2;
    } else {
        hand[card]++;
        hand[hand_size]++;

        if (card >= night_min_id && card <= night_min_id) {
            hand[night_card_count]++;
        }
    }

    print("Picked successfully");
    return true;
}

bool GameState::action_decay(uint8_t* drop_ids, uint8_t* display, uint8_t* hand) {
    return false;
}

bool GameState::action_cook(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand) {
    uint8_t max_count = hand[id];

    if (id < 8) {
        max_count += hand[id + 9] * 2;
    }

    if (count < 3 || count > max_count || display[pan] < 1) {
        return false;
    }

    display[pan]--;
    uint8_t resources = count;

    if (resources == 8 && hand[butter] >= 2) {
        resources -= 8;
        hand[butter] -= 2;
        hand[hand_size] -= 2;
        display[butter] += 2;
    } else {
        while (resources >= 5 && hand[cidre] > 0) {
            resources -= 5;
            hand[cidre]--;
            hand[hand_size]--;
            display[cidre]++;
        }

        while (resources >= 4 && hand[butter] > 0) {
            resources -= 4;
            hand[butter]--;
            hand[hand_size]--;
            display[butter]++;
        }
    }

    if (count <= max_count - 2) {
        hand[id] -= count;
        hand[hand_size] -= count;
        display[id] += count;
    } else {
        if (id < 8 && hand[id + 9] > 0) {
            hand[id + 9]--;
            hand[hand_size]--;
            hand[night_card_count]--;
            display[id + 9]++;
            count -= 2;
        }

        hand[id] -= count;
        hand[hand_size]--;
        display[id] += count;
    }

    return true;
}

bool GameState::action_sell(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand) {
    uint8_t max_count = hand[id];

    if (id < 8) {
        max_count += hand[id + 9] * 2;
    }

    if (count < 2 || count > max_count) {
        return false;
    }

    uint8_t original_count = count;

    if (count <= max_count - 2) {
        hand[id] -= count;
        discard_pile[id] += count;
        hand[hand_size] -= count;
    } else {
        if (id < 8 && hand[id + 9] > 0) {
            hand[id + 9]--;
            discard_pile[id + 9]++;
            hand[hand_size]--;
            hand[night_card_count]--;
            count -= 2;
        }

        hand[id] -= count;
        discard_pile[id] += count;
        hand[hand_size] -= count;
    }

    display[stick] += original_count * cards[id].price;

    return true;
}

bool GameState::action_pan(uint8_t* display, uint8_t* hand) {
    if (hand[pan] == 0) {
        return false;
    }

    hand[pan]--;
    hand[hand_size]--;
    display[pan]++;

    return true;
}

bool GameState::action_pass(uint8_t* display, uint8_t* hand) {
    // action_pick
    int current_capacity = 8 + display[basket] - (display[fly_agaric] > 0 ? 4 : 0) - hand[hand_size];

    if (current_capacity > 0) {
        return false;
    }

    if (current_capacity == 0) {
        unsigned max_reach = min(8, 2 + display[stick]);

        for (unsigned i = 0; i < max_reach && i < forest_pointer; i++) {
            if (forest[i] == fly_agaric || forest[i] == basket) {
                return false;
            }
        }
    }

    // action_decay
    // TODO

    // action_cook
    for (unsigned i = 0; i < night_min_id - 1; i++) {
        if (hand[i] + hand[i + 9] * 2 >= 3) {
            return false;
        }
    }

    if (hand[8] >= 3) {
        return false;
    }

    // action_sell
    for (unsigned i = 0; i < night_min_id; i++) {
        if (hand[i] >= 2) {
            return false;
        }
    }

    for (unsigned i = night_min_id; i <= night_max_id; i++) {
        if (hand[i] >= 1) {
            return false;
        }
    }

    // action_pan
    if (hand[pan] > 0) {
        return false;
    }

    return true;
}

bool GameState::finalize_turn(bool p1) {
    print("Entering finalize turn");

    if (forest_pointer <= 1) {
        print("Game end detected");
        return false;
    }

    if (decay_pile.is_full()) {
        print("Decay pile is full");
        // TODO Add decay pile to discard pile
        
        decay_pile.clear();
    }

    print_var(forest[0]);

    decay_pile.add_card(forest[0]);
    remove_forest_card(0);

    print(decay_pile.str());
    print_var(draw_pointer);
    print_array("draw_pile", draw_pile, draw_pointer + 1);
    print_var(forest_pointer);
    print_array("forest", forest, forest_pointer);
    print("Refilling forest");

    for (; forest_pointer < 8 && draw_pointer > 0; forest_pointer++) {
        forest[forest_pointer] = draw_pile[--draw_pointer];
    }

    print(decay_pile.str());
    print_var(draw_pointer);
    print_array("draw_pile", draw_pile, draw_pointer + 1);
    print_var(forest_pointer);
    print_array("forest", forest, forest_pointer);

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

void GameState::get_p1_view(uint8_t& draw_pointer, uint8_t*& discard_pile,
    uint8_t*& forest, Pile*& decay_pile,
    uint8_t*& display, uint8_t*& hand,
    uint8_t*& opponent_display, uint8_t*& opponent_hand) {

    draw_pointer = this->draw_pointer;
    discard_pile = this->discard_pile;
    forest = this->forest;
    decay_pile = &this->decay_pile;
    display = display_p1;
    hand = hand_p1;
    opponent_display = display_p2;
    opponent_hand = hand_p2;
}

void GameState::get_p2_view(uint8_t& draw_pointer, uint8_t*& discard_pile,
    uint8_t*& forest, Pile*& decay_pile,
    uint8_t*& display, uint8_t*& hand,
    uint8_t*& opponent_display, uint8_t*& opponent_hand) {

    draw_pointer = this->draw_pointer;
    discard_pile = this->discard_pile;
    forest = this->forest;
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

    for (unsigned i = 0; i < sizeof(forest); i++) {
        if (forest[i] != n1) {
            ss << cards[forest[i]].str() << "; ";
        } else {
            ss << (unsigned) forest[i] << "; ";
        }
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
    uint8_t card = draw_pile[--draw_pointer];

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

inline void GameState::remove_forest_card(uint8_t index) {
    print("Entering remove forest card");
    forest_pointer--;

    for (int i = index; i < forest_pointer; i++) {
        forest[i] = forest[i + 1];
    }

    forest[forest_pointer] = -1;

    print("Exiting remove forest card");
}
