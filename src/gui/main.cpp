#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD:src/gui/main.cpp
=======
    MainWindow w;
    w.show();
    //w.startEngine();
>>>>>>> 277e8fde66a8dbe531c8163d6061a9dc63888e1e:src/gui/main.cpp
    Engine* engine = new Engine();
    engine->setHost("10.90.224.238");
    MainWindow w;
    w.setEngine(engine);
    w.showFullScreen();
    engine->start();
    return a.exec();
}
