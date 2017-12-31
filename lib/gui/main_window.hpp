#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "game/game.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	Game* game;

public:
	explicit MainWindow(Game* game);
	~MainWindow();
};

#endif