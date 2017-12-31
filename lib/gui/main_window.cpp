#include "main_window.hpp"

MainWindow::MainWindow(Game* game) :
	QMainWindow(0),
	game(game)
{
	setWindowTitle("Fungi");
	show();
}

MainWindow::~MainWindow() {}