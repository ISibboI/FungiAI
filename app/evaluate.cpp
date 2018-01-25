#include "spdlog.h"
#include <sstream>
#include <fann.h>
#include <nn/NNController.hpp>
#include <game/run/random_controller.hpp>
#include <game/run/game_runner.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

int count_generations() {
    int count = 0;
    std::ifstream probe;
    do {
        count++;
        std::stringstream ss;
        ss << "generation_" << count << "_winner.fann";
        probe = std::ifstream(ss.str());
    } while (probe.is_open());
    return count - 1;
}

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

    constexpr int tries = 100;
    std::mt19937_64 random_engine;
    std::ofstream result("evaluation.csv");

    const int generation_count = count_generations();
    result << generation_count << "\n";

    for (int gen_a = 0; gen_a <= generation_count; gen_a++) {
        #pragma omp parallel for
        for (int gen_b = 0; gen_b <= generation_count; gen_b++) {
            #pragma omp critical
            { std::cout << "Evaluating generation " << gen_a << " winner against " << gen_b << " winner" << std::endl; }

            std::stringstream ss_a;
            ss_a << "generation_" << gen_a << "_winner.fann";
            std::stringstream ss_b;
            ss_b << "generation_" << gen_b << "_winner.fann";
            struct fann* ann_a = fann_create_from_file(ss_a.str().c_str());
            struct fann* ann_b = fann_create_from_file(ss_b.str().c_str());
            if (ann_a == nullptr) {
                throw std::runtime_error("Could not load " + ss_a.str());
            }
            if (ann_b == nullptr) {
                throw std::runtime_error("Could not load " + ss_b.str());
            }

            int wins = 0;
            GameRunner runner;
            for (int i = 0; i < tries; i++) {
                NNController nnc_a("NN_a", ann_a);
                NNController nnc_b("NN_b", ann_b);
                wins += runner.run_game(&nnc_a, &nnc_b, random_engine) ? 1 : 0;
            }

            fann_destroy(ann_a);
            fann_destroy(ann_b);

            #pragma omp critical
            { result << wins / (double) tries << "\n"; }
        }
    }
}