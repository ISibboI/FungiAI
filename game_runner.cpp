#include "game_runner.h"

#include <stdexcept>

using namespace std;

void run_game(GameState& game_state, int& result, action_descriptor (&p1)(uint8_t&, uint8_t*&,
    uint8_t*&, uint8_t*&, uint8_t&, uint8_t*&, uint8_t*&, uint8_t*&, uint8_t*&),
    action_descriptor (&p2)(uint8_t&, uint8_t*&,  uint8_t*&, uint8_t*&, uint8_t&, uint8_t*&,
    uint8_t*&, uint8_t*&, uint8_t*&), void (&event_illegal_turn)()) {

    bool game_finished = false;
    bool turn_p1 = true;
    uint8_t draw_pointer;
    uint8_t* discard_pile;
    uint8_t* forest;
    uint8_t* decay_pile;
    uint8_t decay_pointer;
    uint8_t* display;
    uint8_t* hand;
    uint8_t* opponent_display;
    uint8_t* opponent_hand;

    action_descriptor action;

    do {
        bool illegal_turn = true;

        while (illegal_turn) {
            if (turn_p1) {
                game_state.get_p1_view(draw_pointer, discard_pile, forest,
                    decay_pile, decay_pointer, display, hand, opponent_display,
                    opponent_hand);
                action = p1(draw_pointer, discard_pile, forest, decay_pile,
                    decay_pointer, display, hand, opponent_display, opponent_hand);
            } else {
                game_state.get_p2_view(draw_pointer, discard_pile, forest,
                    decay_pile, decay_pointer, display, hand, opponent_display,
                    opponent_hand);
                action = p2(draw_pointer, discard_pile, forest, decay_pile,
                    decay_pointer, display, hand, opponent_display, opponent_hand);
            }

            switch (action.action) {
            case 1:
                illegal_turn = game_state.action_pick(action.target, action.drop_ids, display, hand);
                break;
            case 2:
                illegal_turn = game_state.action_decay(action.drop_ids, display, hand);
                break;
            case 3:
                illegal_turn = game_state.action_cook(action.target, action.count, display, hand);
                break;
            case 4:
                illegal_turn = game_state.action_sell(action.target, action.count, display, hand);
                break;
            case 5:
                illegal_turn = game_state.action_pan(display, hand);
                break;
            default:
                throw runtime_error("Unknown action: " + (unsigned) action.action);
            }

            if (illegal_turn) {
                event_illegal_turn();
            }
        }

        turn_p1 = !turn_p1;
    } while (!game_finished);

    uint8_t points_p1 = 0;
    uint8_t points_p2 = 0;
    uint8_t shrooms_p1 = 0;
    uint8_t shrooms_p2 = 0;

    for (unsigned i = 0; i < shroom_max_id; i++) {
        shrooms_p1 += game_state.display_p1[i];
        shrooms_p2 += game_state.display_p2[i];
        points_p1 += game_state.display_p1[i] * cards[i].tastyness;
        points_p2 += game_state.display_p2[i] * cards[i].tastyness;
    }

    if (points_p1 == points_p2) {
        if (shrooms_p1 == shrooms_p2) {
            result = 0;
        } else {
            result = (shrooms_p1 > shrooms_p2) * 2 - 1;
        }
    } else {
        result = (points_p1 > points_p2) * 2 - 1;
    }
}
