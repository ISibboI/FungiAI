#include "game_runner.h"
#include "debug.h"
#include "structured_pile.h"

#include <stdexcept>
#include <sstream>

using namespace std;

action_descriptor::action_descriptor() : drop_ids("Drop ids") {}

action_descriptor::~action_descriptor() {}

string action_descriptor::str() {
    stringstream ss;

    ss << "(action: " << (unsigned) action << ", ";
    ss << "target: " << (unsigned) target << ", ";
    ss << "count: " << (unsigned) count << ", ";
    ss << drop_ids.str();

    ss << ")";

    return ss.str();
}

void run_game(GameState& game_state, int& result, action_descriptor (&p1)(uint8_t&, StructuredPile*&,
    Pile*&, Pile*&, StructuredPile*&, HandStructuredPile*&, StructuredPile*&, HandStructuredPile*&),
    action_descriptor (&p2)(uint8_t&, StructuredPile*&,  Pile*&, Pile*&, StructuredPile*&,
    HandStructuredPile*&, StructuredPile*&, HandStructuredPile*&), void (&event_illegal_turn)(action_descriptor&)) {

    bool game_running = true;
    bool turn_p1 = true;
    uint8_t draw_pile_size;
    StructuredPile* discard_pile;
    Pile* forest;
    Pile* decay_pile;
    StructuredPile* display;
    HandStructuredPile* hand;
    StructuredPile* opponent_display;
    HandStructuredPile* opponent_hand;

    action_descriptor action;

    while (game_running) {
        bool successful_turn = false;
        int unsuccessful_tries = 0;

        while (!successful_turn) {
            print("Getting player turn");

            if (turn_p1) {
                game_state.get_p1_view(draw_pile_size, discard_pile, forest,
                    decay_pile, display, hand, opponent_display,
                    opponent_hand);
                action = p1(draw_pile_size, discard_pile, forest, decay_pile,
                    display, hand, opponent_display, opponent_hand);
            } else {
                game_state.get_p2_view(draw_pile_size, discard_pile, forest,
                    decay_pile, display, hand, opponent_display,
                    opponent_hand);
                action = p2(draw_pile_size, discard_pile, forest, decay_pile,
                    display, hand, opponent_display, opponent_hand);
            }

            print("Executing action: " + action.str());

            switch (action.action) {
            case 1:
                successful_turn = game_state.action_pick(action.target, &action.drop_ids, display, hand);
                break;
            case 2:
                successful_turn = game_state.action_decay(&action.drop_ids, display, hand);
                break;
            case 3:
                successful_turn = game_state.action_cook(action.target, action.count, display, hand);
                break;
            case 4:
                successful_turn = game_state.action_sell(action.target, action.count, display, hand);
                break;
            case 5:
                successful_turn = game_state.action_pan(display, hand);
                break;
            case 6:
                successful_turn = game_state.action_pass(display, hand);
                break;
            default:
                throw runtime_error("Unknown action: " + (unsigned) action.action);
            }

            if (!successful_turn) {
                event_illegal_turn(action);
                unsuccessful_tries++;
            }

            if (unsuccessful_tries > 100) {
                print(string("Could not find a correct turn for player ") + (turn_p1 ? "1" : "2"));
                print("Game state:\n" + game_state.str());
                throw runtime_error("Too many incorrect turns");
            }
        }

        game_running = game_state.finalize_turn(turn_p1);
        turn_p1 = !turn_p1;
        print("New game state:\n" + game_state.str());
    }

    int points_p1 = 0;
    int points_p2 = 0;
    int shrooms_p1 = 0;
    int shrooms_p2 = 0;

    for (unsigned i = 0; i < shroom_max_id; i++) {
        shrooms_p1 += game_state.display_p1[i];
        shrooms_p2 += game_state.display_p2[i];
        points_p1 += game_state.display_p1[i] * cards[i].tastyness;
        points_p2 += game_state.display_p2[i] * cards[i].tastyness;
    }

    #ifdef DEBUG
    cout << "Game finished!" << endl;
    cout << "Points player 1 -- 2: " << points_p1 << " -- " << points_p2 << endl;
    cout << "Mushroom count player 1 -- 2: " << shrooms_p1 << " -- " << shrooms_p2 << endl;
    #endif // DEBUG

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
