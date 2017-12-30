#include "main_window.hpp"

MainWindow::MainWindow(Game* game) :
	display_p1(*((nana::form*) this), game->get_p1().get_name()),
	display_p2(*((nana::form*) this), game->get_p2().get_name()),
	game(game)
{
	div("<display_p1><display_p2>");
	nana::form& form = *((nana::form*) this);
	form["display_p1"] << display_p1;
	form["display_p2"] << display_p2;
	collocate();
	show();
}

MainWindow::~MainWindow() {}