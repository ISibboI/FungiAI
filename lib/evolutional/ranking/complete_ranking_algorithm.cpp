#include "complete_ranking_algorithm.hpp"

#include <omp.h>
#include <iostream>

CompleteRankingAlgorithm::CompleteRankingAlgorithm() :
	logger(spdlog::get("CompleteRankingAlgorithm")) {}

void CompleteRankingAlgorithm::rank(vector<EvolutionalNNController*>& population, mt19937_64& random_engine) {
	logger->info("Ranking population...");
	vector<unsigned> points(population.size(), 0);
	vector<omp_lock_t> locks(population.size());
	for (auto& lock : locks) {
		omp_init_lock(&lock);
	}

	#pragma omp parallel for schedule(static, 1)
	for (size_t c1 = 0; c1 < population.size(); c1++) {
		for (size_t c2 = c1 + 1; c2 < population.size(); c2++) {
			omp_set_lock(&locks[c1]);
			omp_set_lock(&locks[c2]);
            bool winner = get_game_runner((unsigned) omp_get_thread_num()).run_game(population[c1], population[c2], random_engine);
			omp_unset_lock(&locks[c2]);
			omp_unset_lock(&locks[c1]);
            #pragma omp critical
            {
                if (winner) {
    				points[c1]++;
	    		} else {
		    		points[c2]++;
			    }
            }
		}
	}

	sort_by(population, points);
	logger->info("Ranked population");
}