#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QIcon>
#include "scroll.h"

namespace Ui
{
    class MouseWindow;
}

class Engine;
class MouseWindow : public QMainWindow
{
    Q_OBJECT
public:
    MouseWindow(QWidget *parent = 0);
    ~MouseWindow();
    void processScrollBarActivity(int delta);
    void setEngine(Engine* engine) { this->engine = engine; }

public slots:
    void leftMouseButtonClicked();
    void rightMouseButtonClicked();
    void toggleButtonClicked();
    void lockButtonPressed();
    void lockButtonReleased();

private:
    Ui::MouseWindow *ui;
    bool locked;
    Engine* engine;
    QIcon open;
    QIcon closed;
};

#endif // MAINWINDOW_H
