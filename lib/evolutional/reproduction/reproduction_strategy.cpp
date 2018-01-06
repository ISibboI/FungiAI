#include "reproduction_strategy.hpp"

ReproductionStrategy::ReproductionStrategy() :
	logger(spdlog::get("ReproductionStrategy")) {}

vector<EvolutionalNNController*> ReproductionStrategy::reproduce_population_destructive(
	vector<EvolutionalNNController*>& population,
	mt19937_64& random_engine
) const {
	vector<EvolutionalNNController*> result = reproduce_population(population, random_engine);

	logger->debug("Deleting old controllers...");
	for (auto* c : population) {
		delete c;
	}
	logger->debug("Deleted old controllers");

	return result;
};