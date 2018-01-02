#ifndef GUI_UTIL_HPP
#define GUI_UTIL_HPP

#include <QLayout>
#include <QWidget>

class GuiUtil {
public:
	static void replace_layout(QWidget* widget, QLayout* new_layout);
};

#endif