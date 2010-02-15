#include <iostream>
#include <QtCore/QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    std::cout << "Connecting" << std::endl;
    if (client.connectTo("dzarg.dy.fi", 6668)) {
        std::cout << "Connected!" << std::endl;

        client.sendMessage("Hello World");
        std::cout << "Text sent!" << std::endl;

        client.sendMouseMovement(200, 200);
        std::cout << "Mouse movement sent!" << std::endl;

        client.sendClick(3);
        std::cout << "Right mouse click sent!" << std::endl;

        client.sendScroll(5);
        std::cout << "Mouse wheel scroll sent!" << std::endl;
    }
    else {
        std::cout << "Connection failed :(" << std::endl;
    }
    return a.exec();
}
