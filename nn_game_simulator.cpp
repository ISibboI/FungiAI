#include "nn_game_simulator.h"

using namespace std;

NNGameSimulator::NNGameSimulator(mt19937& r, struct fann* p1, struct fann* p2) : p1(p1), p2(p2) {
    game_state = new GameState(r);
    inputs = new float[PlayerView::get_nn_encoding_size()];
}

NNGameSimulator::~NNGameSimulator() {
    delete game_state;
    delete inputs;
}

int NNGameSimulator::simulate_game() {
    bool game_running = true;
    bool turn_p1 = true;

    while (game_running) {
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

        if (!game_state->action(action)) {
            return turn_p1 ? -1 : 1;
        }

        delete action;
        delete player_view;
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
