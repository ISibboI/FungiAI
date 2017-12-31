#include "gui/main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication q_application(argc, argv);

	Game game;
	MainWindow main_window(&game);

	return q_application.exec();
}