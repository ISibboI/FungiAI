#ifndef EVOLUTIONAL_OPTIMIZATION_HPP
#define EVOLUTIONAL_OPTIMIZATION_HPP

#include "ranking/ranking_algorithm.hpp"
#include "reproduction/reproduction_strategy.hpp"
#include "spdlog.h"

#include <vector>
#include <random>
#include <memory>

using namespace std;

class EvolutionalOptimization {
private:
	vector<EvolutionalNNController*> population;
	RankingAlgorithm* ranking_algorithm;
	ReproductionStrategy* reproduction_strategy;
	mt19937_64 random_engine;
	unsigned generation;

	shared_ptr<spdlog::logger> logger;

public:
	EvolutionalOptimization(RankingAlgorithm* ranking_algorithm, ReproductionStrategy* reproduction_strategy, unsigned seed);
	~EvolutionalOptimization();

	void set_initial_population(vector<EvolutionalNNController*>& population);
	void set_initial_population(vector<EvolutionalNNController*>&& population);

	void advance_one_generation();
	void advance_n_generations(unsigned n);

	unsigned get_generation() const;
	const vector<EvolutionalNNController*>& get_population() const;
};

#endif