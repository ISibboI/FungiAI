#ifndef FUNGI_AI_EVOLUTIONALCONTROLLER_HPP
#define FUNGI_AI_EVOLUTIONALCONTROLLER_HPP

#include "evolutional/reproduction/reproduction_trait.hpp"
#include "nn/NNController.hpp"

class EvolutionalNNController : public NNController, public ReproductionTrait<EvolutionalNNController> {
public:
    explicit EvolutionalNNController(const string& name, struct fann* ann) : NNController(name, ann) {}
    EvolutionalNNController(const EvolutionalNNController& con);
    ~EvolutionalNNController() override;

    EvolutionalNNController *make_baby(mt19937_64 &random_engine, double randomness) const override;

    struct fann* get_ann();
};


#endif //FUNGI_AI_EVOLUTIONALCONTROLLER_HPP
