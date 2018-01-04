#ifndef CARD_PANEL_HPP
#define CARD_PANEL_HPP

#include "game/cards/card_information.hpp"

#include <QLabel>

class CardPanel : public QLabel {
	Q_OBJECT

private:
	uint8_t id;

public:
	CardPanel(uint8_t id);
	~CardPanel();
};

class MultiCardPanel : public QWidget {
	Q_OBJECT

private:
	uint8_t id;
	uint8_t count;

public:
	MultiCardPanel(uint8_t id, uint8_t count);
	~MultiCardPanel();
};

#endif