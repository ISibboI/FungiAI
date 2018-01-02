#ifndef STRUCTURED_PILE_PANEL_HPP
#define STRUCTURED_PILE_PANEL_HPP

#include "game/data_structures/structured_pile.hpp"
#include "card_panel.hpp"

#include <QGroupBox>
#include <QString>

#include <vector>

using namespace std;

class StructuredPilePanel : public QGroupBox {
	Q_OBJECT

private:
	StructuredPile* structured_pile;

public:
	StructuredPilePanel(StructuredPile* structured_pile, const QString& title);
	~StructuredPilePanel();

	void update();
};

#endif