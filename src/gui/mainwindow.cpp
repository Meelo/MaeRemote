#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), locked(false)
{
    ui->setupUi(this);
    Scroll *scroll = new Scroll(ui->scrollFrame);
    scroll->setMainWindow(this);
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

MainWindow::~MainWindow()
{
    delete ui;
}
