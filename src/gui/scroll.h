#ifndef SCROLL_H
#define SCROLL_H

#include <QWidget>
#include <QMouseEvent>
#include <QMainWindow>

class Scroll : public QWidget
{
public:
	Scroll(QWidget *parent);
	void setMainWindow(QMainWindow *main);

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	int previous;
	QMainWindow *mainWindow;
};

#endif // SCROLL_H
