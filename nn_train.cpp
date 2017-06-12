#include "nn_train.h"

#include <cstring>

using namespace std;

void nn_generate_action_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
        
    }

void nn_generate_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    
    memset(desired_output, 0, Action::get_nn_decoding_size() * sizeof(float));
    memset(output_mask, 0, Action::get_nn_decoding_size() * sizeof(char));
    
    if (game_state->check_any_action(action)) {
        nn_generate_action_correction(game_state, player_view, action, outputs, desired_output, output_mask);
    } else {
        // Action is not possible at all.
        // The first six neurons are the action indicators.
        desired_output[action->id - 1] = outputs[action->id - 1] - 1;
        output_mask[action->id - 1] = 1;
    }
}
