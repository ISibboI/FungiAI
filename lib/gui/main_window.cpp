#include "main_window.hpp"

MainWindow::MainWindow(Game* game, Controller* enemy) :
	game_panel(game, enemy)
{
	auto* layout = new QGridLayout;

	layout->addWidget(&game_panel, 0, 0);

	setLayout(layout);

	setWindowTitle("Fungi");
	show();
}