#ifndef SCROLL_H
#define SCROLL_H

#include <QWidget>
#include <QMouseEvent>
#include <QMainWindow>

class MouseWindow;
class Scroll : public QWidget
{
public:
    Scroll(QWidget *parent);
    void setMouseWindow(MouseWindow *main);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int previous;
    bool moved;
    int counter;
    static const int SENSITIVITY = 50;
    MouseWindow *mouseWindow;
};

#endif // SCROLL_H
