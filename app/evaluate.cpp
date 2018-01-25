#include "spdlog.h"
#include <sstream>
#include <fann.h>
#include <nn/NNController.hpp>
#include <game/run/random_controller.hpp>
#include <game/run/game_runner.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <omp.h>

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

    std::vector<std::vector<struct fann*>> anns(1);
    int generation_count = -1;
    do {
        std::stringstream ss;
        ss << "generation_" << ++generation_count << "_winner.fann";
        anns[0].push_back(fann_create_from_file(ss.str().c_str()));
    } while (anns[0].back() != nullptr);
    anns[0].pop_back();
    for (int i = 1; i < omp_get_max_threads(); i++) {
        anns.emplace_back();
        for (int gen = 0; gen < generation_count; gen++) {
            anns[i].push_back(fann_copy(anns[0][gen]));
        }
    }

    std::vector<double> result_vector((size_t) (generation_count * generation_count));
    int iterations = 0;
    int total_iterations = generation_count * (generation_count + 1) / 2;

    for (int gen_a = 0; gen_a < generation_count; gen_a++) {
        #pragma omp parallel for
        for (int gen_b = gen_a + 1; gen_b < generation_count; gen_b++) {
            #pragma omp critical
            {
                int percentage = 100 * iterations++ / total_iterations;
                std::cout << percentage << "% Evaluating generation " << gen_a << " winner against " << gen_b << " winner" << std::endl;
            }

            int thread_num = omp_get_thread_num();
            int wins = 0;
            GameRunner runner;
            for (int i = 0; i < tries; i++) {
                NNController nnc_a("NN_a", anns[thread_num][gen_a]);
                NNController nnc_b("NN_b", anns[thread_num][gen_b]);
                wins += runner.run_game(&nnc_a, &nnc_b, random_engine) ? 1 : 0;
            }

            result_vector[gen_a * generation_count + gen_b] = wins / (double) tries;
            result_vector[gen_b * generation_count + gen_a] = 1. - wins / (double) tries;
        }
        result_vector[gen_a * generation_count + gen_a] = 0.5;
    }

    std::ofstream result("evaluation.csv");
    result << generation_count << "\n";
    for (const auto& v : result_vector) {
        result << v << "\n";
    }

    for (auto& anns_local : anns) {
        for (auto& ann : anns_local) {
            fann_destroy(ann);
        }
    }
}