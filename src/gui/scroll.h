#ifndef SCROLL_H
#define SCROLL_H

#include <QWidget>
#include <QMouseEvent>
#include <QMainWindow>

class MainWindow;
class Scroll : public QWidget
{
public:
	Scroll(QWidget *parent);
        void setMainWindow(MainWindow *main);

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	int previous;
        MainWindow *mainWindow;
};

#endif // SCROLL_H
