#include "evolutional_optimization.hpp"

EvolutionalOptimization::EvolutionalOptimization(
	RankingAlgorithm* ranking_algorithm,
	ReproductionStrategy* reproduction_strategy,
	unsigned seed
) :
	ranking_algorithm(ranking_algorithm),
	reproduction_strategy(reproduction_strategy),
	random_engine(seed),
	generation(0),
	logger(spdlog::get("EvolutionalOptimization")) {}

EvolutionalOptimization::~EvolutionalOptimization() {
	for (auto* c : population) {
		delete c;
	}
}

void EvolutionalOptimization::set_initial_population(vector<EvolutionalNNController*>& population) {
	set_initial_population(move(population));
}

void EvolutionalOptimization::set_initial_population(vector<EvolutionalNNController*>&& population) {
	logger->info("Setting inital population...");
	this->population = population;
	generation = 0;
	ranking_algorithm->rank(this->population, random_engine);
	logger->info("Initial population set");
}

void EvolutionalOptimization::advance_one_generation() {
	logger->info("Advancing generation {:d} -> {:d}...", generation, generation + 1);
	population = reproduction_strategy->reproduce_population_destructive(population, random_engine);
	ranking_algorithm->rank(this->population, random_engine);
	generation++;
	logger->info("Advanced generation {:d} -> {:d}", generation - 1, generation);
}

void EvolutionalOptimization::advance_n_generations(unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		advance_one_generation();
	}
}

unsigned EvolutionalOptimization::get_generation() const {
	return generation;
}

const vector<EvolutionalNNController*>& EvolutionalOptimization::get_population() const {
	return population;
}