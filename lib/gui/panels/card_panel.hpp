#ifndef CARD_PANEL_HPP
#define CARD_PANEL_HPP

#include "game/cards/card_information.hpp"

#include <QLabel>
#include <QFrame>

class CardPanel : public QLabel {
	Q_OBJECT

private:
	uint8_t id;

signals:
	void released(uint8_t id);

protected:
	void mouseReleaseEvent(QMouseEvent* event);

public:
	CardPanel(uint8_t id);
	~CardPanel();
};

class MultiCardPanel : public QWidget {
	Q_OBJECT

private:
	uint8_t id;
	uint8_t count;
	QFrame q_frame;

public:
	MultiCardPanel(uint8_t id, uint8_t count, QWidget* receiver);
	~MultiCardPanel();
};

#endif