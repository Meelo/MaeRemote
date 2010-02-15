#include <QtCore/QCoreApplication>
#include <iostream>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "Connecting!" << std::endl;
    Client client;
    client.connectTo("dzarg.dy.fi", 6668);
    return a.exec();
}
