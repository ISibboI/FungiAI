#include "reproduction_strategy.hpp"

vector<EvolutionalNNController*> ReproductionStrategy::reproduce_population_destructive(
	vector<EvolutionalNNController*>& population,
	mt19937_64& random_engine
) const {
	vector<EvolutionalNNController*> result = reproduce_population(population, random_engine);
	for (auto* c : population) {
		delete c;
	}

	return result;
};

void ReproductionStrategy::set_randomness(double randomness) {
    this->randomness = randomness;
}

double ReproductionStrategy::get_randomness() const {
    return randomness;
}