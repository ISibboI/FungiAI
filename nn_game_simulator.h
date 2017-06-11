#ifndef NN_GAME_SIMULATOR_H
#define NN_GAME_SIMULATOR_H

#include "game_state.h"
#include "action.h"
#include "player_view.h"

#include <floatfann.h>
#include <random>

class NNGameSimulator {
public:
    NNGameSimulator(std::mt19937& r, struct fann* p1, struct fann* p2);
    ~NNGameSimulator();

    int simulate_game();

    struct fann* p1;
    struct fann* p2;

    GameState* game_state;
    Action* action;
    PlayerView* player_view;
    bool rules_obeyed;

    float* inputs;
    float* outputs;
};

#endif // NN_GAME_SIMULATOR_H
