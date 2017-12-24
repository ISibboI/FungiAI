#include "random_controller.hpp"
#include "game/actions/pick_action.hpp"
#include "game/actions/pick_decay_action.hpp"
#include "game/actions/cook_mushrooms_action.hpp"
#include "game/actions/sell_mushrooms_action.hpp"
#include "game/actions/place_pan_action.hpp"

#include <numeric>

using namespace std;

RandomController::RandomController(const string& name, unsigned seed) :
	EvolutionalController(name),
	random_engine(seed),
	logger(spdlog::get("RandomController")) {}

RandomController::~RandomController() {}

vector<uint8_t> RandomController::random_sequence(uint8_t min, uint8_t count) {
	vector<uint8_t> result(count, 0);
	iota(result.begin(), result.end(), min);
	shuffle(result.begin(), result.end(), random_engine);
	return result;
}

void RandomController::do_turn(Player& me, Player& enemy, Forest& forest) {
	vector<uint8_t> action_order = random_sequence(1, 5);
	DiscardAction discard_action(random_sequence(0, 20));

	for (unsigned action : action_order) {
		bool success;

		switch (action) {
        case 1: {
            logger->trace("Trying PickAction");
            PickAction pick_action(random_sequence(0, 8), &discard_action);
            success = pick_action.execute(me, forest);
        } break;
        case 2: {
            logger->trace("Trying DecayAction");
            PickDecayAction pick_decay_action(&discard_action);
            success = pick_decay_action.execute(me, forest);
        } break;
        case 3: {
            logger->trace("Trying CookMushroomsAction");
            CookMushroomsAction cook_mushrooms_action(random_sequence(0, 9));
            success = cook_mushrooms_action.execute(me, forest);
        } break;
        case 4: {
            logger->trace("Trying SellMushroomsAction");
            SellMushroomsAction sell_mushrooms_action(random_sequence(0, 9));
            success = sell_mushrooms_action.execute(me, forest);
        } break;
        case 5: {
            logger->trace("Trying PlacePanAction");
            PlacePanAction place_pan_action;
            success = place_pan_action.execute(me, forest);
        } break;
        default:
        	logger->error("Unknown action id {}", action);
        	throw runtime_error("Unknown action id");
        }

        if (success) {
        	break;
        }
	}
}

RandomController* RandomController::make_baby(mt19937_64& random_engine) const {
	unsigned seed = (unsigned) random_engine();
	return new RandomController(get_name(), seed);
}