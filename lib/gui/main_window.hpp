#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "game/game.hpp"
#include "gui/panels/game_panel.hpp"

#include <QWidget>

class MainWindow : public QWidget {
	Q_OBJECT

private:
	GamePanel game_panel;

public:
	explicit MainWindow(Game* game);
	~MainWindow();
};

#endif