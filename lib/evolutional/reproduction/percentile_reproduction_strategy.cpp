#include "percentile_reproduction_strategy.hpp"

PercentileReproductionStrategy::PercentileReproductionStrategy(double percentile) :
	percentile(percentile),
	logger(spdlog::get("PercentileReproductionStrategy")) {}

PercentileReproductionStrategy::~PercentileReproductionStrategy() {}

vector<EvolutionalController*> PercentileReproductionStrategy::reproduce_population(
	vector<EvolutionalController*>& population,
	mt19937_64& random_engine
) const {
	logger->info("Reproducing population...");

	vector<EvolutionalController*> result;
	const unsigned limit = (unsigned) (percentile * population.size());
	unsigned index = 0;

	while (result.size() < population.size()) {
		result.push_back(population[index]->make_baby(random_engine));
		index = (index + 1) % limit;
	}

	logger->info("Reproduced population");
	return result;
}