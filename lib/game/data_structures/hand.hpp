#ifndef HAND_HPP
#define HAND_HPP

#include "structured_pile.hpp"

using namespace std;

class Hand : public StructuredPile {
public:
    Hand(const string& name);
    virtual ~Hand() override;

    virtual void add_cards(const Card& card, unsigned count) override;
    virtual void remove_cards(const Card& card, unsigned count) override;
    virtual unsigned card_count(const Card& card) override;

private:
    bool ensure_valid_hand_card(const Card& card);
};

#endif
