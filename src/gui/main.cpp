#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    //w.startEngine();
    Engine* engine = new Engine();
    engine->setHost("10.90.224.238");
    engine->start();
    return a.exec();
}
