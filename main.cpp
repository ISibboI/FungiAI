#include "nn_game_simulator.h"
#include "debug.h"
#include "nn_train.h"

#include <iostream>
#include <floatfann.h>

using namespace std;

int main() {
    cout << "Starting..." << endl;

    size_t input_layer_size = PlayerView::get_nn_encoding_size();
    size_t hidden_layer_size = (PlayerView::get_nn_encoding_size() + Action::get_nn_decoding_size()) / 2;
    size_t output_layer_size = Action::get_nn_decoding_size();

    print_var(input_layer_size);
    print_var(hidden_layer_size);
    print_var(output_layer_size);

    struct fann* player = fann_create_standard(3, input_layer_size, hidden_layer_size, output_layer_size);
    fann_set_activation_function_hidden(player, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(player, FANN_SIGMOID_SYMMETRIC);
    fann_randomize_weights(player, -0.3, 0.3);

    cout << "Initialized NN" << endl;

    mt19937 r;
    bool rules_learned = false;
    float* desired_output = new float[output_layer_size];
    char* output_mask = new char[output_layer_size];

    while (!rules_learned) {
        NNGameSimulator simulator(r, player, player);
        int winner = simulator.simulate_game();

        if (!simulator.rules_obeyed) {
            int looser = 3 - winner;
            cout << "Player " << looser << " didn't obey the rules." << endl;
            cout << "He tried to do\n" << simulator.action->str() << "\nin state\n";
            cout << simulator.game_state->str() << endl;
            
            nn_generate_correction(simulator.game_state, simulator.player_view, simulator.action, simulator.outputs, desired_output, output_mask);
            fann_train_masked(player, simulator.inputs, desired_output, output_mask);
        } else {
            rules_learned = true;
        }

        cout << "Player " << winner << " has won!" << endl;
    }
    
    delete[] output_mask;
    delete[] desired_output;
    fann_destroy(player);

    return 0;
}
