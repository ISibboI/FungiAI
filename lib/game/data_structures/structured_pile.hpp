#ifndef STRUCTURED_PILE_HPP
#define STRUCTURED_PILE_HPP

#include "game/cards/card.hpp"
#include "pile.hpp"
#include "spdlog.h"

#include <string>
#include <vector>

using namespace std;

class StructuredPile : public Pile {
private:
    vector<uint8_t> cards;
    unsigned all_cards_count;
    shared_ptr<spdlog::logger> logger;

public:
    StructuredPile(const string& name);
    virtual ~StructuredPile() override;

    virtual unsigned size() const;
    void add_card(const Card& card);
    virtual void add_cards(const Card& card, unsigned count);
    void remove_card(const Card& card);
    virtual void remove_cards(const Card& card, unsigned count);
    virtual unsigned card_count(const Card& card) const;

    void add_card(uint8_t id);
    virtual void add_cards(uint8_t id, unsigned count);
    void remove_card(uint8_t id);
    virtual void remove_cards(uint8_t id, unsigned count);
    virtual unsigned card_count(uint8_t id) const;

    const vector<uint8_t>& get_card_counts();

    virtual void check_size() const;

    virtual void clear();

    virtual string str() const;
    virtual string str(const string& prefix) const;
};

#endif // STRUCTURED_PILE_H
