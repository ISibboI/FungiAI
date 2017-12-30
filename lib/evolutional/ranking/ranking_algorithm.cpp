#include "ranking_algorithm.hpp"

#include <algorithm>
#include <numeric>

using namespace std;

RankingAlgorithm::RankingAlgorithm() {}

RankingAlgorithm::~RankingAlgorithm() {}

GameRunner& RankingAlgorithm::get_game_runner() {
	return game_runner;
}

void RankingAlgorithm::sort_by(vector<EvolutionalController*>& population, vector<unsigned>& points) const {
	vector<unsigned> permutation(points.size(), 0);
	iota(permutation.begin(), permutation.end(), 0);

	sort(permutation.begin(), permutation.end(), [&points](const unsigned& a, const unsigned& b) {
		return points[a] < points[b];
	});

	vector<EvolutionalController*> copy = population;

	for (unsigned i = 0; i < population.size(); i++) {
		population[i] = copy[permutation[i]];
	}
}