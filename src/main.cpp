#include "nn_game_simulator.h"
#include "debug.h"
#include "nn_train.h"
#include "number_logger.h"

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
    fann_save(player, "data/initial_network.fann");

    cout << "Initialized NN" << endl;

    mt19937 r;
    NumberLogger logger("data/completed_turns.csv");
    bool rules_learned = false;
    float* desired_output = new float[output_layer_size];
    char* output_mask = new char[output_layer_size];
    const unsigned MAX_TRIES = 1000000000;
    unsigned tries = 0;

    while (!rules_learned && tries++ < MAX_TRIES) {
        NNGameSimulator simulator(r, player, player);
        int winner = simulator.simulate_game();

        if (!simulator.rules_obeyed) {
            int looser = 3 - winner;
            cout << "Player " << looser << " didn't obey the rules." << endl;
            cout << "He tried to do\n" << simulator.action->str() << "\nin state\n";
            cout << simulator.game_state->str() << endl;
            
            cout << "Training NN..." << endl;
            nn_train_to_correctness(simulator.game_state, simulator.player_view, simulator.action, player, simulator.inputs, simulator.outputs, desired_output, output_mask);
            
            cout << "Player would now do " << simulator.action->str() << endl;
        } else {
            rules_learned = true;
        }

        logger.log_number(simulator.completed_turns);
        cout << "Player " << winner << " has won!" << endl;
    }
    
    delete[] output_mask;
    delete[] desired_output;
    
    fann_save(player, "data/trained_network.fann");
    fann_destroy(player);

    return 0;
}
