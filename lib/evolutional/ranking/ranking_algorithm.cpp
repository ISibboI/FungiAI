#include "ranking_algorithm.hpp"

#include <algorithm>
#include <numeric>
#include <omp.h>

using namespace std;

GameRunner& RankingAlgorithm::get_game_runner(size_t index) {
    //#pragma omp critical
	if (index >= game_runners.size()) {
        game_runners.resize(index + 1);
    }
    return game_runners[index];
}

void RankingAlgorithm::sort_by(vector<EvolutionalNNController*>& population, vector<unsigned>& points) const {
	vector<unsigned> permutation(points.size(), 0);
	iota(permutation.begin(), permutation.end(), 0);

	sort(permutation.begin(), permutation.end(), [&points](const unsigned& a, const unsigned& b) {
		return points[a] > points[b];
	});

	vector<EvolutionalNNController*> copy = population;

	for (unsigned i = 0; i < population.size(); i++) {
		population[i] = copy[permutation[i]];
	}
}