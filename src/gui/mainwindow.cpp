#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"
#include "connectionwindow.h"

MainWindow::MainWindow(ConnectionWindow* connectionWindow, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), connectionWindow(connectionWindow), locked(false)
{
    ui->setupUi(this);
    Scroll *scroll = new Scroll(ui->scrollFrame);
    scroll->setMainWindow(this);
    ui->leftMouseButton->setStyleSheet("background-color: #dddddd;");
    ui->rightMouseButton->setStyleSheet("background-color: #dddddd;");
    ui->lockButton->setStyleSheet("background-color: #dddddd;");
    ui->toggleButton->setStyleSheet("background-color: #dddddd;");
    open.addFile("openlock_small.png");
    closed.addFile("closedlock_small.png");
}

void MainWindow::processScrollBarActivity(int delta)
{
    if (!locked) {
        qDebug() << delta;
        engine->sendScroll(delta);
    }
}

void MainWindow::leftMouseButtonClicked()
{
    if (!locked) {
        qDebug() << "Left button clicked";
        engine->sendClick(1);
    }
}

void MainWindow::rightMouseButtonClicked()
{
    if (!locked) {
        qDebug() << "Right button clicked";
        engine->sendClick(3);
    }
}

void MainWindow::toggleButtonClicked()
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

void MainWindow::lockButtonPressed()
{
    locked = !locked;
    qDebug() << locked;
}

void MainWindow::lockButtonReleased()
{
    locked = !locked;
    qDebug() << locked;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    connectionWindow->terminateConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
    engine->terminateConnection();
    engine->wait();
    delete engine;
}
