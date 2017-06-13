#ifndef NN_TRAIN_H
#define NN_TRAIN_H

#include "game_state.h"
#include "player_view.h"
#include "action.h"

#include <floatfann.h>

void nn_punish_output(size_t i, float* outputs, float* desired_output, char* output_mask);

void nn_punish_output_range(size_t offset, size_t length, float* outputs, float* desired_output, char* output_mask);

void nn_generate_action_correction_pick(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_action_correction_decay(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_action_correction_cook(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_action_correction_sell(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_action_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);

void nn_generate_correction(GameState* game_state, PlayerView* player_view, Action* action,
    float* outputs, float* desired_output, char* output_mask);
    
void nn_train_to_correctness(GameState* game_state, PlayerView* player_view, Action* action, struct fann* player, float* inputs, float* outputs, float* desired_output, char* output_mask);

#endif // NN_TRAIN_H
