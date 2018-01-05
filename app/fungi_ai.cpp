#include "evolutional/evolutional_optimization.hpp"
#include "evolutional/ranking/complete_ranking_algorithm.hpp"
#include "evolutional/reproduction/percentile_reproduction_strategy.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int main() {
    spdlog::stdout_logger_st("DiscardAction");
    spdlog::stdout_logger_st("PickAction");
    spdlog::stdout_logger_st("PickDecayAction");
    spdlog::stdout_logger_st("CookMushroomsAction");
    spdlog::stdout_logger_st("SellMushroomsAction");
    spdlog::stdout_logger_st("PlacePanAction");
    spdlog::stdout_logger_st("EvolutionalRandomController");
    spdlog::stdout_logger_st("EvolutionalOptimization");
    spdlog::stdout_logger_st("PercentileReproductionStrategy");
    spdlog::stdout_logger_st("CompleteRankingAlgorithm");
    spdlog::stdout_logger_st("Forest");
    spdlog::stdout_logger_st("ReproductionStrategy");

    spdlog::set_level(spdlog::level::trace);
    shared_ptr<spdlog::logger> logger = spdlog::stdout_logger_st("Main");

    CompleteRankingAlgorithm ranking_algorithm;
    PercentileReproductionStrategy reproduction_strategy(0.5);
    EvolutionalOptimization evolutional_optimization(&ranking_algorithm, &reproduction_strategy, 656737);

    vector<EvolutionalController*> initial_population;

    for (unsigned i = 0; i < 10; i++) {
        stringstream ss;
        ss << "Number " << i << " loves random";

        //initial_population.push_back(new EvolutionalRandomController(ss.str(), i));
    }

    evolutional_optimization.set_initial_population(initial_population);
    evolutional_optimization.advance_n_generations(10);

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

    logger->info("Success!");
    return 0;
}
