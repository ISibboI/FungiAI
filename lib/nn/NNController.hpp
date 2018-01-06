#ifndef FUNGI_AI_NNCONTROLLER_HPP
#define FUNGI_AI_NNCONTROLLER_HPP

#include "game/run/controller.hpp"
#include "fann.h"
#include "game/actions/CombinedAction.hpp"

class NNController : public Controller {
private:
    vector<float> nn_input;
    CombinedAction combined_action;

protected:
    struct fann* ann;

public:
    NNController(const string& name, struct fann* ann);
    ~NNController() override = default;

    void do_turn(Game &game, bool p1) override;
};


#endif //FUNGI_AI_NNCONTROLLER_HPP
