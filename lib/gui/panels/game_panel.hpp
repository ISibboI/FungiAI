#ifndef GAME_PANEL_HPP
#define GAME_PANEL_HPP

#include "gui/panels/display_panel.hpp"
#include "game/game.hpp"

#include <QWidget>

class GamePanel : public QWidget {
	Q_OBJECT

private:
	DisplayPanel* display_p1;
	DisplayPanel* display_p2;

	Game* game;

public:
	GamePanel(QWidget* parent, Game* game);
	~GamePanel();
};

#endif