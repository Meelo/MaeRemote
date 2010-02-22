#include <QDebug>
#include "mousewindow.h"
#include "ui_mousewindow.h"
#include "engine.h"

MouseWindow::MouseWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MouseWindow), locked(false),
        engine(0)
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
    if (!locked) {
        qDebug() << delta;
        engine->sendScroll(delta);
    }
}

void MouseWindow::leftMouseButtonClicked()
{
    if (!locked) {
        qDebug() << "Left button clicked";
        engine->sendClick(1);
    }
}

void MouseWindow::rightMouseButtonClicked()
{
    if (!locked) {
        qDebug() << "Right button clicked";
        engine->sendClick(3);
    }
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

MouseWindow::~MouseWindow()
{
    delete ui;
    delete engine;
}
