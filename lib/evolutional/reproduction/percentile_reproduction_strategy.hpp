#ifndef PERCENTILE_REPRODUCTION_STRATEGY_HPP
#define PERCENTILE_REPRODUCTION_STRATEGY_HPP

#include "reproduction_strategy.hpp"
#include "spdlog.h"

class PercentileReproductionStrategy : public ReproductionStrategy {
private:
	double percentile;
	shared_ptr<spdlog::logger> logger;

public:
	PercentileReproductionStrategy(double percentile);
	~PercentileReproductionStrategy();

	virtual vector<EvolutionalController*> reproduce_population(
		vector<EvolutionalController*>& population,
		mt19937_64& random_engine) const;
};

#endif