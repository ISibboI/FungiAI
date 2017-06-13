#include "game_state.h"
#include "debug.h"

#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

GameState::GameState(mt19937& r) : draw_pile("Draw pile", sizeof(initial_draw_pile)), forest("Forest", 8), decay_pile("Decay pile", 4),
    discard_pile("Discard pile"), display_p1("Display p1"), display_p2("Display p2"), hand_p1("Hand p1"), hand_p2("Hand p2") {

    draw_pile.add_cards(initial_draw_pile, sizeof(initial_draw_pile));
    shuffle(draw_pile.get_offset(), draw_pile.get_limit(), r);

    forest.make_space(8);
    draw_pile.remove_cards(draw_pile.size() - 8, 8, forest.get_offset());

    display_p1.add_card(pan);
    display_p2.add_card(pan);

    for (int i = 0; i < 3; i++) {
        draw_initial_card(display_p1, hand_p1);
        draw_initial_card(display_p2, hand_p2);
    }
}

GameState::~GameState() {}

bool GameState::check_general_pickup(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand, StructuredPile* picked_cards) {
    uint8_t drop_size = 0;
    int8_t pick_all_size = picked_cards->pick_all_size();
    int8_t remaining_capacity = hand->get_remaining_capacity(display);

    if (pick_all_size > remaining_capacity) {
        return false;
    }

    if ((*picked_cards)[fly_agaric] > 0 && display->get_count(fly_agaric) == 0) {
        drop_size = (uint8_t) max(0, 4 - remaining_capacity + pick_all_size);

        for (unsigned i = 0; i < special_min_id; i++) {
            if (drop_ids->get_count(i) > hand->get_count(i) + (*picked_cards)[i]) {
                return false;
            }
        }

        for (unsigned i = special_min_id; i < cards_size; i++) {
            if (drop_ids->get_count(i) > 0) {
                throw runtime_error("Can't drop cards that never go into the hand");
            }
        }
    }

    return drop_ids->size() >= drop_size;
}

bool GameState::check_action_pick(uint8_t index, StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    if (index >= forest.size()) {
        return false;
    }

    uint8_t card = forest[index];
    uint8_t price = max(0, index - 1);
    StructuredPile pick_pile("Pick pile");
    pick_pile.add_card(card);

    return price <= display->get_count(stick) && check_general_pickup(drop_ids, display, hand, &pick_pile);
}

bool GameState::check_action_decay(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    StructuredPile* structured_decay_pile = decay_pile.structurize();
    bool result = check_general_pickup(drop_ids, display, hand, structured_decay_pile);
    delete structured_decay_pile;

    return result;
}

bool GameState::check_action_cook(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    if (id >= night_min_id) {
        return false;
    }

    return display->get_count(pan) > 0 && count >= 3 && hand->get_effective_shroom_count(id) >= count;
}

bool GameState::check_action_sell(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    if (id >= night_min_id) {
        return false;
    }

    return count >= 2 && hand->get_effective_shroom_count(id) >= count;
}

bool GameState::check_action_pan(StructuredPile* display, HandStructuredPile* hand) {
    return hand->get_count(pan) >= 1;
}

bool GameState::check_action_pass(StructuredPile* display, HandStructuredPile* hand) {
    int8_t capacity = hand->get_remaining_capacity(display);
    uint8_t forest_limit = min(forest.size(), (uint8_t) (2 + display->get_count(stick)));

    // Pick
    for (unsigned i = 0; i < forest_limit; i++) {
        if (cards[forest[i]].size <= capacity) {
            return false;
        }
    }

    // Decay
    if (decay_pile.pick_all_size() <= capacity) {
        return false;
    }

    // Cook & Sell
    for (unsigned i = 0; i < night_min_id; i++) {
        if (hand->get_count(i) >= 2) {
            return false;
        }
    }

    if (hand->get_night_card_count() > 0) {
        return false;
    }

    // Pan
    if (check_action_pan(display, hand)) {
        return false;
    }

    return true;
}

bool GameState::check_action(Action* action) {
    switch (action->id) {
    case 1:
        return check_action_pick(action->target, action->drop_ids, action->display, action->hand);
    case 2:
        return check_action_decay(action->drop_ids, action->display, action->hand);
    case 3:
        return check_action_cook(action->target, action->count, action->display, action->hand);
    case 4:
        return check_action_sell(action->target, action->count, action->display, action->hand);
    case 5:
        return check_action_pan(action->display, action->hand);
    case 6:
        return check_action_pass(action->display, action->hand);
    default:
        throw runtime_error("Unknown action id");
    }
}

bool GameState::check_any_action_pick(StructuredPile* display, HandStructuredPile* hand) {
    uint8_t max_index = min(forest.size(), (uint8_t) (2 + display->get_count(stick)));
    uint8_t hand_capacity = hand->get_remaining_capacity(display);
    
    for (unsigned i = 0; i < max_index; i++) {
        if (cards[forest[i]].size <= hand_capacity) {
            return true;
        }
    }
    
    return false;
}

bool GameState::check_any_action_decay(StructuredPile* display, HandStructuredPile* hand) {
    return decay_pile.pick_all_size() <= hand->get_remaining_capacity(display);
}

bool GameState::check_any_action_cook(StructuredPile* display, HandStructuredPile* hand) {
    if (!display->get_count(pan)) {
        return false;
    }
    
    for (unsigned i = 0; i < night_min_id; i++) {
        if (hand->get_effective_shroom_count(i) >= 3) {
            return true;
        }
    }
    
    return false;
}

bool GameState::check_any_action_sell(StructuredPile* display, HandStructuredPile* hand) {
    for (unsigned i = 0; i < night_min_id; i++) {
        if (hand->get_effective_shroom_count(i) >= 2) {
            return true;
        }
    }
    
    return false;
}

bool GameState::check_any_action_pan(StructuredPile* display, HandStructuredPile* hand) {
    return hand->get_count(pan) >= 1;
}

bool GameState::check_any_action_pass(StructuredPile* display, HandStructuredPile* hand) {
    return check_action_pass(display, hand);
}

bool GameState::check_any_action(Action* action) {
    switch (action->id) {
    case 1:
        return check_any_action_pick(action->display, action->hand);
    case 2:
        return check_any_action_decay(action->display, action->hand);
    case 3:
        return check_any_action_cook(action->display, action->hand);
    case 4:
        return check_any_action_sell(action->display, action->hand);
    case 5:
        return check_any_action_pan(action->display, action->hand);
    case 6:
        return check_any_action_pass(action->display, action->hand);
    default:
        throw runtime_error("Unknown action id");
    }
}

bool GameState::action_pick(uint8_t index, StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    if (!check_action_pick(index, drop_ids, display, hand)) {
        return false;
    }

    uint8_t card = forest.remove_card(index);

    if (card >= special_min_id) {
        if (card == fly_agaric) {
            if ((*display)[fly_agaric] > 0) {
                discard_pile.add_card(fly_agaric);
            }

            display->set_cards(fly_agaric, 2);
        } else {
            if (card != basket) {
                throw runtime_error("Card can only be basket here");
            }

            display->add_cards(basket, 2);
        }
    } else {
        hand->add_card(card);
    }

    for (unsigned i = 0; i < special_min_id && hand->get_remaining_capacity(display) < 0; i++) {
        hand->remove_cards(i, min((*drop_ids)[i], hand->get_count(i)));
    }

    uint8_t price = (uint8_t) max(0, index - 1);
    display->remove_cards(stick, price);

    return true;
}

bool GameState::action_decay(StructuredPile* drop_ids, StructuredPile* display, HandStructuredPile* hand) {
    if (!check_action_decay(drop_ids, display, hand)) {
        return false;
    }

    while (decay_pile.size() > 0) {
        uint8_t card = decay_pile.remove_last_card();

        if (card >= special_min_id) {
            if (card == fly_agaric) {
                if ((*display)[fly_agaric] > 0) {
                    discard_pile.add_card(fly_agaric);
                }

                display->set_cards(fly_agaric, 2);
            } else {
                if (card != basket) {
                    throw runtime_error("Card can only be basket here");
                }

                display->add_cards(basket, 2);
            }
        } else {
            hand->add_card(card);
        }
    }

    for (unsigned i = 0; i < special_min_id && hand->get_remaining_capacity(display) < 0; i++) {
        hand->remove_cards(i, min((*drop_ids)[i], hand->get_count(i)));
    }

    return true;
}

bool GameState::action_cook(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    if (!check_action_cook(id, count, display, hand)) {
        return false;
    }

    bool night_card_cooked = hand->remove_shrooms_maximizing_space(id, count);

    if (count >= 10 && (*hand)[cidre] >= 2) {
        hand->remove_cards(cidre, 2);
        display->add_cards(cidre, 2);
    } else if (count >= 9 && (*hand)[cidre] >= 1 && (*hand)[butter] >= 1) {
        hand->remove_card(cidre);
        hand->remove_card(butter);
        display->add_card(cidre);
        display->add_card(butter);
    } else if (count >= 8 && (*hand)[butter] >= 2) {
        hand->remove_cards(butter, 2);
        display->add_cards(butter, 2);
    } else if (count >= 5 && (*hand)[cidre] >= 1) {
        hand->remove_card(cidre);
        display->add_card(cidre);
    } else if (count >= 4 && (*hand)[butter] >= 1) {
        hand->remove_card(butter);
        display->add_card(butter);
    }

    if (night_card_cooked) {
        display->add_card(id + to_night_card);
        count -= 2;
    }

    display->add_cards(id, count);
    display->remove_card(pan);

    return true;
}

bool GameState::action_sell(uint8_t id, uint8_t count, StructuredPile* display, HandStructuredPile* hand) {
    if (!check_action_sell(id, count, display, hand)) {
        return false;
    }

    bool night_card_sold = hand->remove_shrooms_maximizing_space(id, count);

    display->add_cards(stick, count * cards[id].price);

    if (night_card_sold) {
        discard_pile.add_card(id + to_night_card);
        count -= 2;
    }

    discard_pile.add_cards(id, count);

    return true;
}

bool GameState::action_pan(StructuredPile* display, HandStructuredPile* hand) {
    if (!check_action_pan(display, hand)) {
        return false;
    }

    hand->remove_card(pan);
    display->add_card(pan);

    return true;
}

bool GameState::action_pass(StructuredPile* display, HandStructuredPile* hand) {
    return check_action_pass(display, hand);
}

bool GameState::action(Action* action) {
    switch (action->id) {
    case 1:
        return action_pick(action->target, action->drop_ids, action->display, action->hand);
    case 2:
        return action_decay(action->drop_ids, action->display, action->hand);
    case 3:
        return action_cook(action->target, action->count, action->display, action->hand);
    case 4:
        return action_sell(action->target, action->count, action->display, action->hand);
    case 5:
        return action_pan(action->display, action->hand);
    case 6:
        return action_pass(action->display, action->hand);
    default:
        throw runtime_error("Unknown action id");
    }
}

vector<Action*> GameState::generate_actions_pick(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;
    uint8_t max_affordable = (uint8_t) max(0, display->get_count(stick) - 1) + 2;

    for (unsigned i = 0; i < max_affordable && i < forest.size(); i++) {
        StructuredPile* drop_ids = new StructuredPile("Drop ids");

        if (check_action_pick(i, drop_ids, display, hand)) {
            result.push_back(new Action(1, i, drop_ids, display, hand));
        } else {
            delete drop_ids;
        }
    }

    return result;
}

vector<Action*> GameState::generate_actions_decay(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;
    StructuredPile* drop_ids = new StructuredPile("Drop ids");

    if (check_action_decay(drop_ids, display, hand)) {
        result.push_back(new Action(2, drop_ids, display, hand));
    } else {
        delete drop_ids;
    }

    return result;
}

vector<Action*> GameState::generate_actions_cook(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;

    for (unsigned i = 0; i < night_min_id; i++) {
        uint8_t count = hand->get_effective_shroom_count(i);

        if (count >= 3) {
            result.push_back(new Action(3, i, count, display, hand));
        }
    }

    return result;
}

vector<Action*> GameState::generate_actions_sell(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;

    for (unsigned i = 0; i < night_min_id; i++) {
        uint8_t count = hand->get_effective_shroom_count(i);

        if (count >= 2) {
            result.push_back(new Action(4, i, count, display, hand));
        }
    }

    return result;
}

vector<Action*> GameState::generate_actions_pan(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;

    if (check_action_pan(display, hand)) {
        result.push_back(new Action(5, display, hand));
    }

    return result;
}

vector<Action*> GameState::generate_actions_pass(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> result;

    if (check_action_pass(display, hand)) {
        result.push_back(new Action(6, display, hand));
    }

    return result;
}

vector<Action*> GameState::generate_actions(StructuredPile* display, HandStructuredPile* hand) {
    vector<Action*> pick = generate_actions_pick(display, hand);
    vector<Action*> decay = generate_actions_decay(display, hand);
    vector<Action*> cook = generate_actions_cook(display, hand);
    vector<Action*> sell = generate_actions_sell(display, hand);
    vector<Action*> pan = generate_actions_pan(display, hand);
    vector<Action*> pass = generate_actions_pass(display, hand);
    vector<Action*> result;
    result.reserve(pick.size() + decay.size() + cook.size() + sell.size() + pan.size() + pass.size());
    result.insert(result.end(), pick.begin(), pick.end());
    result.insert(result.end(), decay.begin(), decay.end());
    result.insert(result.end(), cook.begin(), cook.end());
    result.insert(result.end(), sell.begin(), sell.end());
    result.insert(result.end(), pan.begin(), pan.end());
    result.insert(result.end(), pass.begin(), pass.end());
    return result;
}

bool GameState::finalize_turn(bool p1) {
    if (forest.size() <= 1) {
        print("Game end detected");
        return false;
    }

    if (decay_pile.is_full()) {
        while (decay_pile.size() > 0) {
            discard_pile.add_card(decay_pile.remove_last_card());
        }

        decay_pile.clear();
    }

    decay_pile.add_card(forest.remove_card(0));

    while (forest.size() < 8 && draw_pile.size() > 0) {
        forest.add_card(draw_pile.remove_last_card());
    }

    if (p1) {
        if (display_p1[fly_agaric] > 0) {
            display_p1.remove_card(fly_agaric);

            if (display_p1[fly_agaric] == 0) {
                discard_pile.add_card(fly_agaric);
            }
        }
    } else {
        if (display_p2[fly_agaric] > 0) {
            display_p2.remove_card(fly_agaric);

            if (display_p2[fly_agaric] == 0) {
                discard_pile.add_card(fly_agaric);
            }
        }
    }

    return true;
}

PlayerView* GameState::get_p1_view() {
    return new PlayerView(draw_pile.size(), &discard_pile, &forest, &decay_pile,
    &display_p1, &hand_p1, &display_p2, &hand_p2);
}

PlayerView* GameState::get_p2_view() {
    return new PlayerView(draw_pile.size(), &discard_pile, &forest, &decay_pile,
    &display_p2, &hand_p2, &display_p1, &hand_p1);
}

string GameState::str() {
    stringstream ss;

    ss << "     " << hand_p1.str() << "\n";
    ss << "  " << display_p1.str() << "\n";
    ss << "      " << forest.str() << "\n";
    ss << "  " << decay_pile.str() << "\n";
    ss << "  " << display_p2.str() << "\n";
    ss << "     " << hand_p2.str() << "\n";
    ss << discard_pile.str();

    return ss.str();
}

inline void GameState::draw_initial_card(StructuredPile& display, HandStructuredPile& hand) {
    uint8_t card = draw_pile.remove_last_card();

    // Baskets directly go into the display
    if (card == basket) {
        display_p1.add_cards(basket, 2);
    } else if (card == fly_agaric) {
        // Fly agarics go directly into the discard_pile
        discard_pile.add_card(fly_agaric);
    } else {
        // Everything else goes into the players hand
        hand.add_card(card);
    }
}