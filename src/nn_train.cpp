#include "nn_train.h"

#include <cstring>
#include <stdexcept>

using namespace std;

void nn_punish_output(size_t i, float* outputs, float* desired_output, char* output_mask) {
    desired_output[i] = outputs[i] - 1;
    output_mask[i] = 1;
}

void nn_punish_output_range(const size_t offset, const size_t length, float* outputs, float* desired_output, char* output_mask) {
    for (size_t i = offset; i < offset + length; i++) {
        desired_output[i] = outputs[i] - 1;
        output_mask[i] = 1;
    }
}

void nn_generate_action_correction_pick(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    // Picking is possible, but the target or the drop_ids are wrong.
    // We ignore the dropping mechanism for now and just punish the target.
    // Targets start from 6.
    nn_punish_output(6 + action->target, outputs, desired_output, output_mask);
    
    // TODO Correct drop_ids
}

void nn_generate_action_correction_decay(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    // Picking the decay pile is possible, but the drop_ids are wrong.
    // We ignore the dropping mechanism for now and just punish the action.
    nn_punish_output(action->id - 1, outputs, desired_output, output_mask);
    
    // TODO Correct drop_ids
}

void nn_generate_action_correction_cook(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    // Cooking is possible, but target or count is wrong, or there is no pan.
    if (action->count < 3) {
        // The count is wrong, cooking is only allowed with 3 or more cards.
        // So let's punish the count. It starts from 6 + night_min_id and is
        // offset by 2. So it can only be 2 in this case.
        nn_punish_output(6 + night_min_id, outputs, desired_output, output_mask);
        return;
    }
    
    uint8_t target_count = player_view->hand->get_count(action->target);
    
    if (target_count < 3) {
        // The target can't be cooked, so let's punish the target.
        nn_punish_output(6 + action->target, outputs, desired_output, output_mask);
        return;
    }
    
    if (player_view->display->get_count(pan) == 0) {
        // No pan, no cooking. Punish the action.
        nn_punish_output(action->id - 1, outputs, desired_output, output_mask);
        return;
    }
    
    // Now both count and target hand cards are big enough, and there is a pan,
    // so count has to be too big.
    nn_punish_output_range(6 + night_min_id + target_count - 2 + 1, 12 - target_count - 1, outputs, desired_output, output_mask);
}

void nn_generate_action_correction_sell(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    // Selling is possible, but target is wrong.
    // So, let's punish the target. Targets start from 6.
    nn_punish_output(6 + action->target, outputs, desired_output, output_mask);
}
    

void nn_generate_action_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    
    switch (action->id) {
        case 1: nn_generate_action_correction_pick(game_state, player_view, action, outputs, desired_output, output_mask); break;
        case 2: nn_generate_action_correction_decay(game_state, player_view, action, outputs, desired_output, output_mask); break;
        case 3: nn_generate_action_correction_cook(game_state, player_view, action, outputs, desired_output, output_mask); break;
        case 4: nn_generate_action_correction_sell(game_state, player_view, action, outputs, desired_output, output_mask); break;
        default: throw runtime_error("No action correction possible");
    }
}

void nn_generate_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask) {
    
    memset(desired_output, 0, Action::get_nn_decoding_size() * sizeof(float));
    memset(output_mask, 0, Action::get_nn_decoding_size() * sizeof(char));
    
    if (game_state->check_any_action(action)) {
        nn_generate_action_correction(game_state, player_view, action, outputs, desired_output, output_mask);
    } else {
        // Action is not possible at all.
        // The first six neurons are the action indicators and actions start from 1.
        nn_punish_output(action->id - 1, outputs, desired_output, output_mask);
    }
}
