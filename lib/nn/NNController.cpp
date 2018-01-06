#include "NNController.hpp"
#include "nn/NNCoder.hpp"

NNController::NNController(const string &name, struct fann *ann) :
    Controller(name),
    ann(ann),
    nn_input(NNCoder::get_nn_input_size(), 0),
    combined_action() {}

void NNController::do_turn(Game &game, bool p1) {
    NNCoder::encode(game, p1, nn_input.data());
    float* nn_output = fann_run(ann, nn_input.data());
    NNCoder::decode(nn_output, combined_action);
    combined_action.execute(game.get_player(p1), game.get_forest());
}
