#ifndef FUNGI_AI_RANDOMCONTROLLER_HPP
#define FUNGI_AI_RANDOMCONTROLLER_HPP

#include "game/player.hpp"
#include "game/forest.hpp"
#include "controller.hpp"

class RandomController : public Controller {
private:
    mt19937_64 random_engine;
    shared_ptr<spdlog::logger> logger;

    vector<uint8_t> random_sequence(uint8_t min, uint8_t count);

public:
    RandomController(const string& name, unsigned seed);
    ~RandomController() override = default;

    void do_turn(Player& me, Player& enemy, Forest& forest) override;
};


#endif //FUNGI_AI_RANDOMCONTROLLER_HPP
