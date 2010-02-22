#include <QDebug>
#include "mousewindow.h"
#include "ui_mousewindow.h"
#include "engine.h"
#include "connectionwindow.h"

MouseWindow::MouseWindow(ConnectionWindow* connectionWindow, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MouseWindow), connectionWindow(connectionWindow),
        locked(false), engine(0)
{
    ui->setupUi(this);
    Scroll *scroll = new Scroll(ui->scrollFrame);
    scroll->setMouseWindow(this);
    ui->leftMouseButton->setStyleSheet("background-color: #dddddd;");
    ui->rightMouseButton->setStyleSheet("background-color: #dddddd;");
    ui->lockButton->setStyleSheet("background-color: #dddddd;");
    ui->toggleButton->setStyleSheet("background-color: #dddddd;");
    open.addFile("openlock_small.png");
    closed.addFile("closedlock_small.png");
}

void MouseWindow::processScrollBarActivity(int delta)
{
    qDebug() << delta;
    engine->sendScroll(delta);
}

void MouseWindow::leftMouseButtonClicked()
{
    qDebug() << "Left button clicked";
    engine->sendClick(1);
}

void MouseWindow::rightMouseButtonClicked()
{
    qDebug() << "Right button clicked";
}

void MouseWindow::toggleButtonClicked()
{
    locked = !locked;
    if (locked) {
        ui->toggleButton->setIcon(closed);
    }
    else {
        ui->toggleButton->setIcon(open);
    }
    qDebug() << locked;
}

void MouseWindow::lockButtonPressed()
{
    locked = !locked;
    qDebug() << locked;
}

void MouseWindow::lockButtonReleased()
{
    locked = !locked;
    qDebug() << locked;
}

void MouseWindow::closeEvent(QCloseEvent *event)
{
    connectionWindow->terminateConnection(this);
    QMainWindow::closeEvent(event);
}

MouseWindow::~MouseWindow()
{
    delete ui;
    engine->terminateConnection();
    engine->wait();
    delete engine;
}
