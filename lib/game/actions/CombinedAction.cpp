//
// Created by sibbo on 06.01.18.
//

#include "CombinedAction.hpp"
#include "game/io/strings.hpp"

#include <sstream>

CombinedAction::CombinedAction() :
    Action("CombinedAction", 10),
    pick_action(&discard_action),
    pick_decay_action(&discard_action) {}

CombinedAction::CombinedAction(vector<uint8_t> action_order, vector<uint8_t> pick_order, vector<uint8_t> discard_order, vector<uint8_t> cook_order, vector<uint8_t> sell_order) :
    Action("CombinedAction", 10),
    discard_action(move(discard_order)),
    pick_action(move(pick_order), &discard_action),
    pick_decay_action(&discard_action),
    cook_mushrooms_action(move(cook_order)),
    sell_mushrooms_action(move(sell_order)),
    action_order(move(action_order))
{}

bool CombinedAction::execute(Player &player, Forest &forest) {
    for (uint8_t action : action_order) {
        switch (action) {
            case 0: if (pick_action.execute(player, forest)) return true; else break;
            case 1: if (pick_decay_action.execute(player, forest)) return true; else break;
            case 2: if (cook_mushrooms_action.execute(player, forest)) return true; else break;
            case 3: if (sell_mushrooms_action.execute(player, forest)) return true; else break;
            case 4: if (place_pan_action.execute(player, forest)) return true; else break;
            default: throw runtime_error("Unknown action");
        }
    }

    return false;
}

string CombinedAction::str(const string &prefix) const {
    const string subprefix(prefix + "  ");
    stringstream ss;
    ss << prefix << get_name() << ":\n";
    ss << prefix << "  Action order: " << Strings::str(action_order) << "\n";
    ss << prefix << discard_action.str(subprefix);
    ss << prefix << pick_action.str(subprefix);
    ss << prefix << pick_decay_action.str(subprefix);
    ss << prefix << cook_mushrooms_action.str(subprefix);
    ss << prefix << sell_mushrooms_action.str(subprefix);
    ss << prefix << place_pan_action.str(subprefix);
    return ss.str();
}

vector<uint8_t>& CombinedAction::get_action_order() {
    return action_order;
}

vector<uint8_t>& CombinedAction::get_pick_order() {
    return pick_action.get_pick_order();
}

vector<uint8_t>& CombinedAction::get_discard_order() {
    return discard_action.get_discard_order();
}

vector<uint8_t>& CombinedAction::get_cook_order() {
    return cook_mushrooms_action.get_cook_order();
}

vector<uint8_t>& CombinedAction::get_sell_order() {
    return sell_mushrooms_action.get_sell_order();
}
