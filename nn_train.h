#ifndef NN_TRAIN_H
#define NN_TRAIN_H

#include "game_state.h"
#include "player_view.h"
#include "action.h"

void nn_generate_action_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

#endif // NN_TRAIN_H
