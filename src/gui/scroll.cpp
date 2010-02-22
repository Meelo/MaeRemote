#include <QDebug>
#include "scroll.h"
#include "mousewindow.h"

Scroll::Scroll(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(790,100);
    this->setStyleSheet("background-color: grey;");
}

void Scroll::setMouseWindow(MouseWindow *main)
{
    mouseWindow = main;
}

void Scroll::mouseMoveEvent(QMouseEvent *event)
{
    mouseWindow->processScrollBarActivity(event->x()-previous);
    previous = event->x();
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
