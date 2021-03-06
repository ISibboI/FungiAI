#ifndef REPRODUCTION_STRATEGY_HPP
#define REPRODUCTION_STRATEGY_HPP

#include "evolutional/EvolutionalNNController.hpp"
#include "spdlog.h"

#include <random>

using namespace std;

class ReproductionStrategy {
private:
	double randomness = 0.1;

public:
	ReproductionStrategy() = default;
	virtual ~ReproductionStrategy() = default;

	virtual vector<EvolutionalNNController*> reproduce_population(
		vector<EvolutionalNNController*>& population,
		mt19937_64& random_engine) const = 0;
	virtual vector<EvolutionalNNController*> reproduce_population_destructive(
		vector<EvolutionalNNController*>& population,
		mt19937_64& random_engine) const;
    void set_randomness(double randomness);
    double get_randomness() const;
};

#endif