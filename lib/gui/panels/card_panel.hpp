#ifndef CARD_PANEL_HPP
#define CARD_PANEL_HPP

#include "game/cards/card_information.hpp"

#include <QWidget>

class CardPanel : public QWidget {
	Q_OBJECT

private:
	uint8_t id;

public:
	CardPanel(uint8_t id);
	~CardPanel();
};

#endif