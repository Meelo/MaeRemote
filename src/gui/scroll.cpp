#include <QDebug>
#include "scroll.h"
#include "mainwindow.h"

Scroll::Scroll(QWidget *parent) : QWidget(parent)
{
    //this->setMouseTracking(true);
    this->setFixedSize(790,100);
    this->setStyleSheet("background-color: grey;");
}

void Scroll::setMainWindow(MainWindow *main)
{
    mainWindow = main;
}

void Scroll::mouseMoveEvent(QMouseEvent *event)
{
    mainWindow->processScrollBarActivity(event->x()-previous);
    previous = event->x();
    //qDebug() << event->x();
}

void Scroll::mousePressEvent(QMouseEvent *event)
{
    previous = event->x();
    qDebug() << "pressed!";
}

void Scroll::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "released!";
}
