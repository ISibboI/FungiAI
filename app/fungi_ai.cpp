#include "game/game.hpp"

#include <iostream>
#include <floatfann.h>
#include <random>

using namespace std;

int main() {
    Game game;
    mt19937_64 random_engine;

    game.initialize(random_engine);
    cout << game.str() << endl;

    /*cout << "Starting..." << endl;

    size_t input_layer_size = PlayerView::get_nn_encoding_size();
    size_t output_layer_size = Action::get_nn_decoding_size();

    print_var(input_layer_size);
    print_var(output_layer_size);
    
    const unsigned NUM_LAYERS = 10;
    unsigned layer_sizes[NUM_LAYERS];
    layer_sizes[0] = input_layer_size;
    layer_sizes[NUM_LAYERS - 1] = output_layer_size;
    
    for (unsigned i = 1; i < NUM_LAYERS - 1; i++) {
        layer_sizes[i] = (input_layer_size * (NUM_LAYERS - i) + output_layer_size * i) / NUM_LAYERS;
    }

    struct fann* player = fann_create_standard_array(NUM_LAYERS, layer_sizes);
    fann_set_activation_function_hidden(player, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(player, FANN_SIGMOID_SYMMETRIC);
    fann_set_learning_rate(player, 0.1);
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

    return 0; */
}
