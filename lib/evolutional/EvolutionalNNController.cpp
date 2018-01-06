//
// Created by sibbo on 06.01.18.
//

#include "EvolutionalNNController.hpp"

EvolutionalNNController::~EvolutionalNNController() {
    fann_destroy(ann);
}