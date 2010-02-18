#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "startupwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Engine* engine = new Engine();
    engine->setHost("10.90.224.238");
    MainWindow w;
    w.setEngine(engine);
    w.showFullScreen();
	engine->start();
//	StartupWindow sw;
//	sw.show();
    return a.exec();
}
