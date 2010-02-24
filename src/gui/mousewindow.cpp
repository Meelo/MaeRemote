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
//    ui->leftMouseButton->setStyleSheet("background-color: #dddddd;");
//    ui->rightMouseButton->setStyleSheet("background-color: #dddddd;");
//    ui->lockButton->setStyleSheet("background-color: #dddddd;");
//    ui->toggleButton->setStyleSheet("background-color: #dddddd;");
//    open.addFile("openlock_small.png");
//    closed.addFile("closedlock_small.png");
    setFocusPolicy(Qt::StrongFocus);
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
    engine->toggleLocked();
    if (engine->isLocked()) {
        ui->toggleButton->setIcon(closed);
    }
    else {
        ui->toggleButton->setIcon(open);
    }
    qDebug() << engine->isLocked();
}

void MouseWindow::lockButtonPressed()
{
    engine->toggleLocked();
    qDebug() << engine->isLocked();
}

void MouseWindow::lockButtonReleased()
{
    engine->toggleLocked();
    qDebug() << engine->isLocked();
}

void MouseWindow::closeEvent(QCloseEvent *event)
{
    connectionWindow->terminateConnection(this);
    QMainWindow::closeEvent(event);
}

void MouseWindow::keyPressEvent (QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Enter:
        engine->sendText("__RETURN__");
        break;
    default:
        engine->sendText(event->text().toLatin1());
    }
    qDebug() << "Key: " << event->key() << " as text: " << event->text();
}

MouseWindow::~MouseWindow()
{
    delete ui;
    engine->terminateConnection();
    engine->wait();
    delete engine;
}
