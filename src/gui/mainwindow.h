#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QIcon>
#include "scroll.h"

namespace Ui
{
    class MainWindow;
}

class Engine;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void processScrollBarActivity(int delta);
    void setEngine(Engine* engine) { this->engine = engine; }

public slots:
    void leftMouseButtonClicked();
    void rightMouseButtonClicked();
    void toggleButtonClicked();
    void lockButtonPressed();
    void lockButtonReleased();

private:
    Ui::MainWindow *ui;
    bool locked;
    Engine* engine;
    QIcon open;
    QIcon closed;
};

#endif // MAINWINDOW_H
