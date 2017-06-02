#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "cards.h"

#include <algorithm>
#include <random>

const uint8_t n1 = (uint8_t) -1;

const uint8_t initial_draw_pile[84] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Card("Honey fungus", 1, 1),
    1, 1, 1, 1, 1, 1, 1, 1, // Card("Tree Ear", 1, 2),
    2, 2, 2, 2, 2, 2, // Card("Lawyer's Wig", 2, 1),
    3, 3, 3, 3, 3, // Card("Shiitake", 2, 2),
    4, 4, 4, 4, 4, // Card("Hen of the Woods", 3, 1),
    5, 5, 5, 5, // Card("Birch bolete", 3, 2),
    6, 6, 6, 6, // Card("Porcini", 3, 3),
    7, 7, 7, 7, // Card("Chanterelle", 4, 2),
    8, 8, 8, // Card("Morels", 6, 4),
    9, // Card("Night Honey fungus", 2, 2),
    10, // Card("Night Tree Ear", 2, 4),
    11, // Card("Night Lawyer's Wig", 4, 2),
    12, // Card("Night Shiitake", 4, 4),
    13, // Card("Night Hen of the Woods", 6, 2),
    14, // Card("Night Birch bolete", 6, 4),
    15, // Card("Night Porcini", 6, 6),
    16, // Card("Night Chanterelle", 8, 4),
    17, 17, 17, // Card("Butter", 3, 4),
    18, 18, 18, // Card("Cidre", 5, 5),
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, // Card("Pan", -1, -1),
    20, 20, 20, 20, 20, // Card("Basket", -1, -1),
    // Card("Moon", -1, -1),
    22, 22, 22, 22, 22 // Card("Fly agaric", -1, -1),
    // Card("Stick", -1, -1)
};

const uint8_t hand_size = 20;
const uint8_t night_card_count = 21;

class GameState {
public:
    GameState(std::mt19937& r);
    ~GameState();

    bool action_pick(uint8_t index, uint8_t* drop_ids, uint8_t* display, uint8_t* hand);
    bool action_decay(uint8_t* drop_ids, uint8_t* display, uint8_t* hand);
    bool action_cook(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand);
    bool action_sell(uint8_t id, uint8_t count, uint8_t* display, uint8_t* hand);
    bool action_pan(uint8_t* display, uint8_t* hand);
    bool action_pass(uint8_t* display, uint8_t* hand);

    bool finalize_turn(bool p1);

    void get_p1_view(uint8_t& draw_pointer, uint8_t*& discard_pile,
        uint8_t*& forest, uint8_t*& decay_pile, uint8_t& decay_pointer,
        uint8_t*& display, uint8_t*& hand,
        uint8_t*& opponent_display, uint8_t*& opponent_hand);
    void get_p2_view(uint8_t& draw_pointer, uint8_t*& discard_pile,
        uint8_t*& forest, uint8_t*& decay_pile, uint8_t& decay_pointer,
        uint8_t*& display, uint8_t*& hand,
        uint8_t*& opponent_display, uint8_t*& opponent_hand);

    std::string str();

    uint8_t draw_pile[sizeof(initial_draw_pile)];
    uint8_t draw_pointer;
    uint8_t discard_pile[cards_size - 1];
    uint8_t forest[8];
    uint8_t forest_pointer;
    uint8_t decay_pile[4];
    uint8_t decay_pointer;

    uint8_t display_p1[cards_size];
    uint8_t display_p2[cards_size];
    uint8_t hand_p1[cards_size - 2];
    uint8_t hand_p2[cards_size - 2];

private:
    inline void draw_initial_card(uint8_t* display, uint8_t* hand);
    inline void remove_forest_card(uint8_t index);
};

#endif // GAME_STATE_H
