#include "game/game.hpp"
#include "game/actions/pick_action.hpp"
#include "game/actions/pick_decay_action.hpp"
#include "game/actions/cook_mushrooms_action.hpp"
#include "game/actions/sell_mushrooms_action.hpp"
#include "game/actions/place_pan_action.hpp"

#include "spdlog.h"

#include <iostream>
#include <floatfann.h>
#include <random>
#include <numeric>

using namespace std;

int main() {
    spdlog::stdout_logger_st("DiscardAction");
    spdlog::stdout_logger_st("PickAction");
    spdlog::stdout_logger_st("PickDecayAction");
    spdlog::stdout_logger_st("CookMushroomsAction");
    spdlog::stdout_logger_st("SellMushroomsAction");
    spdlog::stdout_logger_st("PlacePanAction");

    spdlog::set_level(spdlog::level::trace);
    shared_ptr<spdlog::logger> logger = spdlog::stdout_logger_st("Main");

    Game game;
    mt19937_64 random_engine;

    game.initialize(random_engine);
    cout << game.str() << endl;

    vector<uint8_t> discard_order(24, 0);
    iota(discard_order.begin(), discard_order.end(), 0);
    DiscardAction discard_action(move(discard_order));

    vector<uint8_t> pick_order(8, 0);
    iota(pick_order.begin(), pick_order.end(), 0);
    PickAction pick_action(move(pick_order), &discard_action);

    PickDecayAction pick_decay_action(&discard_action);

    vector<uint8_t> cook_order(9, 0);
    iota(cook_order.begin(), cook_order.end(), 0);
    CookMushroomsAction cook_mushrooms_action(move(cook_order));

    vector<uint8_t> sell_order(9, 0);
    iota(sell_order.begin(), sell_order.end(), 0);
    SellMushroomsAction sell_mushrooms_action(move(sell_order));

    PlacePanAction place_pan_action;

    uniform_int_distribution<> actions(1, 5);

    for (unsigned i = 0; i < 30; i++) {
        switch (actions(random_engine)) {
        case 1: 
            logger->trace("Trying 1");
            pick_action.execute(game.get_p1(), game.get_forest()); break;
        case 2:
            logger->trace("Trying 2");
            pick_decay_action.execute(game.get_p1(), game.get_forest()); break;
        case 3:
            logger->trace("Trying 3");
            cook_mushrooms_action.execute(game.get_p1(), game.get_forest()); break;
        case 4:
            logger->trace("Trying 4");
            sell_mushrooms_action.execute(game.get_p1(), game.get_forest()); break;
        case 5:
            logger->trace("Trying 5");
            place_pan_action.execute(game.get_p1(), game.get_forest()); break;
        }

        game.post_turn_actions();
        logger->trace("Current state\n{}", game.str());
    }

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
