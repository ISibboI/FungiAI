#ifndef FUNGI_AI_COMBINEDACTION_HPP
#define FUNGI_AI_COMBINEDACTION_HPP

#include "actions.hpp"

class CombinedAction : public Action {
private:
    DiscardAction discard_action;
    PickAction pick_action;
    PickDecayAction pick_decay_action;
    CookMushroomsAction cook_mushrooms_action;
    SellMushroomsAction sell_mushrooms_action;
    PlacePanAction place_pan_action;

    vector<uint8_t> action_order;

public:
    CombinedAction();
    CombinedAction(vector<uint8_t> action_order, vector<uint8_t> pick_order, vector<uint8_t> discard_order, vector<uint8_t> cook_order, vector<uint8_t> sell_order);
    ~CombinedAction() override = default;

    bool execute(Player& player, Forest& forest) override;

    string str(const string& prefix) const override;

    vector<uint8_t>& get_action_order();
    vector<uint8_t>& get_pick_order();
    vector<uint8_t>& get_discard_order();
    vector<uint8_t>& get_cook_order();
    vector<uint8_t>& get_sell_order();
};


#endif //FUNGI_AI_COMBINEDACTION_HPP
