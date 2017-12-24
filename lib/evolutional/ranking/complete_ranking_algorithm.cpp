#include "complete_ranking_algorithm.hpp"

CompleteRankingAlgorithm::CompleteRankingAlgorithm() :
	logger(spdlog::get("CompleteRankingAlgorithm")) {}

CompleteRankingAlgorithm::~CompleteRankingAlgorithm() {}

void CompleteRankingAlgorithm::rank(vector<EvolutionalController*>& population, mt19937_64& random_engine) {
	logger->info("Ranking population...");
	vector<unsigned> points(population.size(), 0);

	for (auto c1 = population.begin(); c1 != population.end(); c1++) {
		for (auto c2 = c1 + 1; c2 != population.end(); c2++) {
			if (get_game_runner().run_game(*c1, *c2, random_engine)) {
				points[c1 - population.begin()]++;
			} else {
				points[c2 - population.begin()]++;
			}
		}
	}

	sort_by(population, points);
	logger->info("Ranked population");
}