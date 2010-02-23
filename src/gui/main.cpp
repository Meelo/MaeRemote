#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mousewindow.h"
#include "connectionwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow cw;

// use fullscreen on Maemo5, on others use windowed mode.
#ifdef __ARMEL__
    cw.showFullScreen();
#else
    cw.show();
#endif

    return a.exec();
}
