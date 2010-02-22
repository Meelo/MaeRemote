#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QtGui/QMainWindow>
#include <QIcon>
#include "scroll.h"

namespace Ui
{
    class MainWindow;
}

class ConnectionWindow;
class Engine;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(ConnectionWindow* connectionWindow, QWidget *parent = 0);
    ~MainWindow();
    void processScrollBarActivity(int delta);
    void setEngine(Engine* engine) { this->engine = engine; }

public slots:
    void leftMouseButtonClicked();
    void rightMouseButtonClicked();
    void toggleButtonClicked();
    void lockButtonPressed();
    void lockButtonReleased();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    ConnectionWindow *connectionWindow;
    bool locked;
    Engine* engine;
    QIcon open;
    QIcon closed;
};

#endif // MAINWINDOW_H
