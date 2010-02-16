#include <iostream>
#include <QtCore/QCoreApplication>
#include <QThread>
#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include "client.h"

class MyThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

class SensorData
{
    QByteArray line;
    QFile file;

public:
    SensorData(const QString& filename) : file(filename) {}
    bool update()
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        line = file.readLine();
        file.close();
    }
    QByteArray getLine() const { return line; }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    std::cout << "Connecting" << std::endl;
    if (client.connectTo("lolcathost", 6668)) {
        std::cout << "Connected!" << std::endl;

        client.sendMessage("Hello World");
        std::cout << "Text sent!" << std::endl;
        SensorData sensor("in.txt");
        for (int i = 0; i < 5; ++i) {
            sensor.update();
            client.sendMessage(sensor.getLine());
            MyThread::msleep(100);
            client.sendMouseMovement(200, 200);
            std::cout << "Mouse movement sent!" << std::endl;
        }

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
