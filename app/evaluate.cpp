#include "spdlog.h"
#include <sstream>
#include <fann.h>
#include <nn/NNController.hpp>
#include <game/run/random_controller.hpp>
#include <game/run/game_runner.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

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
    spdlog::stdout_logger_st("RandomController");

    constexpr int tries = 1000;
    std::mt19937_64 random_engine;
    std::ofstream result("evaluation.csv");

    for (int generation = 0; generation <= 100; generation++) {
        std::cout << "Evaluating generation " << generation << std::endl;
        std::stringstream ss;
        ss << "generation_" << generation << "_winner.fann";
        struct fann* ann = fann_create_from_file(ss.str().c_str());
        if (ann == nullptr) {
            throw std::runtime_error("Could not load " + ss.str());
        }
        
        int wins = 0;
        for (int i = 0; i < tries; i++) {
            NNController nnc("NN", ann);
            RandomController rc("Random", (unsigned) i);
            GameRunner runner;
            wins += runner.run_game(&nnc, &rc, random_engine) ? 1 : 0;
        }

        fann_destroy(ann);
        result << wins / (float) tries << "\n";
    }
}