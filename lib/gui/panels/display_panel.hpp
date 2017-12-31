#ifndef DISPLAY_PANEL_HPP
#define DISPLAY_PANEL_HPP

#include <QGridLayout>

class DisplayPanel : public QGridLayout {
	Q_OBJECT

public:
	DisplayPanel();
	~DisplayPanel();
};

#endif