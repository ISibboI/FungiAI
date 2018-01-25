#include "EvolutionalNNController.hpp"

EvolutionalNNController::EvolutionalNNController(const EvolutionalNNController &con) :
        NNController(con.get_name(), fann_copy(con.ann)) {}

EvolutionalNNController::~EvolutionalNNController() {
    fann_destroy(ann);
}

EvolutionalNNController *EvolutionalNNController::make_baby(mt19937_64 &random_engine, const double randomness) const {
    struct fann* ann = fann_copy(this->ann);
    std::uniform_int_distribution<size_t> distribution(0, ann->total_connections);
    std::normal_distribution<fann_type> normal(0.f, .1f);
    for (int i = 0; i < randomness * ann->total_connections; i++) {
        size_t index = distribution(random_engine);
        ann->weights[index] *= normal(random_engine) + 1.f;
    }
    for (int i = 0; i < randomness * ann->total_connections; i++) {
        size_t index = distribution(random_engine);
        ann->weights[index] += normal(random_engine);
    }

    return new EvolutionalNNController(get_name(), ann);
}

struct fann* EvolutionalNNController::get_ann() {
    return ann;
}
