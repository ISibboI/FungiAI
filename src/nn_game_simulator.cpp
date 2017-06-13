#include "nn_game_simulator.h"
#include "debug.h"

#include <iostream>

using namespace std;

NNGameSimulator::NNGameSimulator(mt19937& r, struct fann* p1, struct fann* p2) : p1(p1), p2(p2) {
    game_state = new GameState(r);
    inputs = new float[PlayerView::get_nn_encoding_size()];
    action = 0;
    player_view = 0;
}

NNGameSimulator::~NNGameSimulator() {
    delete game_state;
    delete[] inputs;

    if (action != 0) {
        delete action;
    }

    if (player_view != 0) {
        delete player_view;
    }
}

int NNGameSimulator::simulate_game() {
    bool game_running = true;
    bool turn_p1 = true;
    rules_obeyed = true;
    completed_turns = 0;

    while (game_running) {
        // cout << "Starting turn of player " << (turn_p1 ? 1 : 2) << endl;
        struct fann* current_player;

        if (turn_p1) {
            current_player = p1;
            player_view = game_state->get_p1_view();
        } else {
            current_player = p2;
            player_view = game_state->get_p2_view();
        }

        player_view->encode_for_nn(inputs);
        outputs = fann_run(current_player, inputs);
        action = new Action(outputs, player_view->display, player_view->hand);

        // cout << "Game state is:\n" << game_state->str() << endl;
        // cout << "Player " << (turn_p1 ? 1 : 2) << " does " << action->str() << endl;

        if (!game_state->action(action)) {
            rules_obeyed = false;
            #ifdef DEBUG
            cout << "Game ended early after " << completed_turns << " completed turns" << endl;
            #endif // DEBUG
            return turn_p1 ? 2 : 1;
        }

        delete action;
        delete player_view;
        action = 0;
        player_view = 0;

        game_running = game_state->finalize_turn(turn_p1);
        turn_p1 = !turn_p1;
        completed_turns++;
    }

    int points_p1 = 0;
    int points_p2 = 0;
    int shrooms_p1 = 0;
    int shrooms_p2 = 0;

    for (unsigned i = 0; i < shroom_max_id; i++) {
        shrooms_p1 += game_state->display_p1[i];
        shrooms_p2 += game_state->display_p2[i];
        points_p1 += game_state->display_p1[i] * cards[i].tastyness;
        points_p2 += game_state->display_p2[i] * cards[i].tastyness;
    }

    #ifdef DEBUG
    cout << "Game finished!" << endl;
    cout << "Points player 1 -- 2: " << points_p1 << " -- " << points_p2 << endl;
    cout << "Mushroom count player 1 -- 2: " << shrooms_p1 << " -- " << shrooms_p2 << endl;
    #endif // DEBUG

    if (points_p1 == points_p2) {
        if (shrooms_p1 == shrooms_p2) {
            return 0;
        } else {
            return 2 - (shrooms_p1 > shrooms_p2);
        }
    } else {
        return 2 - (points_p1 > points_p2);
    }
}
