#ifndef PERCENTILE_REPRODUCTION_STRATEGY_HPP
#define PERCENTILE_REPRODUCTION_STRATEGY_HPP

#include "reproduction_strategy.hpp"
#include "spdlog.h"

class PercentileReproductionStrategy : public ReproductionStrategy {
private:
	double percentile;
	shared_ptr<spdlog::logger> logger;

public:
	explicit PercentileReproductionStrategy(double percentile);
	~PercentileReproductionStrategy() override = default;

	virtual vector<EvolutionalNNController*> reproduce_population(
		vector<EvolutionalNNController*>& population,
		mt19937_64& random_engine) const;
};

#endif