#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mousewindow.h"
#include "connectionwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow cw;
    cw.showFullScreen();
    return a.exec();
}
