#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "game/game.hpp"

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

class MainWindow : public nana::form {
private:
	nana::label display_p1;
	nana::label display_p2;
	nana::label forest;

	Game* game;

public:
	MainWindow(Game* game);
	~MainWindow();
};

#endif