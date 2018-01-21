#include <evolutional/ranking/complete_ranking_algorithm.hpp>
#include <evolutional/reproduction/percentile_reproduction_strategy.hpp>
#include <evolutional/evolutional_optimization.hpp>
#include <nn/NNCoder.hpp>
#include "spdlog.h"

int main(int argc, char** argv) {
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
    //spdlog::set_level(spdlog::level::trace);

    constexpr int initial_pop_size = 100;
    vector<EvolutionalNNController*> initial_pop;
    initial_pop.reserve(initial_pop_size);
    for (int i = 0; i < initial_pop_size; i++) {
        struct fann* ann = fann_create_standard(2, NNCoder::get_nn_input_size(), NNCoder::get_nn_output_size());
        initial_pop.push_back(new EvolutionalNNController("EvoCon", ann));
    }

    CompleteRankingAlgorithm ranker;
    PercentileReproductionStrategy reproducer(0.5);
    EvolutionalOptimization optimizer(&ranker, &reproducer, 0);
    optimizer.set_initial_population(initial_pop);
    optimizer.set_save_generation_winner(true);
    optimizer.advance_n_generations(100);

    return 0;
}