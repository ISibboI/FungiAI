#ifndef REPRODUCTION_STRATEGY_HPP
#define REPRODUCTION_STRATEGY_HPP

#include "evolutional/evolutional_controller.hpp"
#include "spdlog.h"

#include <random>

using namespace std;

class ReproductionStrategy {
private:
	shared_ptr<spdlog::logger> logger;

public:
	ReproductionStrategy();
	~ReproductionStrategy();

	virtual vector<EvolutionalController*> reproduce_population(
		vector<EvolutionalController*>& population,
		mt19937_64& random_engine) const = 0;
	virtual vector<EvolutionalController*> reproduce_population_destructive(
		vector<EvolutionalController*>& population,
		mt19937_64& random_engine) const;
};

#endif