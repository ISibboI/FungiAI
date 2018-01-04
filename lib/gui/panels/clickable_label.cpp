#include "clickable_label.hpp"

ClickableLabel::ClickableLabel(const QString& text) : QLabel(text) {}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event) {
	emit released();
}