#ifndef CLICKABLE_LABEL_HPP
#define CLICKABLE_LABEL_HPP

#include <QLabel>

class ClickableLabel : public QLabel {
	Q_OBJECT

signals:
	void released();

public:
	ClickableLabel(const QString& text);
	~ClickableLabel();

	void mouseReleaseEvent(QMouseEvent* event);
};

#endif