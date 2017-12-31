#include "main_window.hpp"

MainWindow::MainWindow(Game* game) :
	QMainWindow(0)
{
	game_panel = new GamePanel(this, game);

	setWindowTitle("Fungi");
	show();
}

MainWindow::~MainWindow() {}