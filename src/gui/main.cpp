#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "startupwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartupWindow sw;
    sw.show();
    return a.exec();
}
