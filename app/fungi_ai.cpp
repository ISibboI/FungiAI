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

    vector<EvolutionalNNController*> initial_population;

    for (unsigned i = 0; i < 10; i++) {
        stringstream ss;
        ss << "Number " << i << " loves random";

        //initial_population.push_back(new EvolutionalNNController(ss.str(), ));
    }

    evolutional_optimization.set_initial_population(initial_population);
    evolutional_optimization.advance_n_generations(10);

    logger->info("Success!");
    return 0;
}
