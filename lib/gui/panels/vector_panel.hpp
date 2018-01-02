#ifndef VECTOR_PANEL_HPP
#define VECTOR_PANEL_HPP

#include "card_panel.hpp"
#include "gui/util/gui_util.hpp"

#include <QGroupBox>
#include <QString>

#include <vector>

using namespace std;

class VectorPanel : public QGroupBox {
	Q_OBJECT

private:
	vector<uint8_t>* cards;
	int delimiter;

public:
	VectorPanel(vector<uint8_t>* cards, const QString& title);
	~VectorPanel();

	void update();
	void set_delimiter(int delimiter);
};

#endif