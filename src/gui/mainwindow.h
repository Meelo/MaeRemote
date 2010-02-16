#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "scroll.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void processScrollBarActivity(int delta);

public slots:
	void leftMouseButtonClicked();
	void rightMouseButtonClicked();
	void toggleButtonClicked();
	void lockButtonPressed();
	void lockButtonReleased();

private:
    Ui::MainWindow *ui;
	bool locked;
	bool tempLocked;
};

#endif // MAINWINDOW_H
