#include <QDebug>
#include "scroll.h"
#include "mousewindow.h"

Scroll::Scroll(QWidget *parent) : QWidget(parent), moved(false), counter(0)
{
    this->setFixedSize(480, 100);
}

void Scroll::setMouseWindow(MouseWindow *main)
{
    mouseWindow = main;
}

void Scroll::mouseMoveEvent(QMouseEvent *event)
{
    int delta = event->x() - previous;
    counter += delta;
    if (abs(counter) > 75) {
        mouseWindow->processScrollBarActivity(counter / 75);
        counter = 0;
        moved = true;
    }
    previous = event->x();
}

void Scroll::mousePressEvent(QMouseEvent *event)
{
    moved = false;
    counter = 0;

    previous = event->x();
    qDebug() << "pressed!";
}

void Scroll::mouseReleaseEvent(QMouseEvent *event)
{
    if (!moved) {
        mouseWindow->middleMouseButtonClicked();
    }
    moved = false;
    qDebug() << "released!";
}
