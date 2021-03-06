#include "gui_util.hpp"

#include <QLayoutItem>

void GuiUtil::replace_layout(QWidget* widget, QLayout* new_layout) {
	if (widget->layout()) {
		while (QLayoutItem* item = widget->layout()->takeAt(0)) {
			item->widget()->deleteLater();
			delete item;
		}

		delete widget->layout();
	}

	if (new_layout != 0) {
		widget->setLayout(new_layout);
	}
}