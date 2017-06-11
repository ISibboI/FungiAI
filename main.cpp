#include "nn_game_simulator.h"

#include <iostream>
#include <floatfann.h>

using namespace std;

int main() {
    struct fann* player = fann_create_standard(3, PlayerView::get_nn_encoding_size(), (PlayerView::get_nn_encoding_size() + Action::get_nn_decoding_size()) / 2, Action::get_nn_decoding_size());
    fann_set_activation_function_hidden(player, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(player, FANN_SIGMOID_SYMMETRIC);
    fann_randomize_weights(player, -0.3, 0.3);

    mt19937 r(7356L);
    NNGameSimulator simulator(r, player, player);
    int winner = simulator.simulate_game();

    fann_destroy(player);

    cout << "Player " << winner << " has won!";

    return 0;
}
