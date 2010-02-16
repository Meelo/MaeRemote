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
    static const qint16 NOISE = 40;
    QString line;
    QFile file;

    qint16 dx;
    qint16 dy;
    qint16 dz;

    qint16 x;
    qint16 y;
    qint16 z;

public:
    SensorData(const QString& filename) : file(filename), 
    dx(0), dy(0), dz(0), x(0), y(0), z(0) {}

    bool update()
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        
        QTextStream in(&file);
        line = in.readLine();
        
        file.close();
        return true;
    }

    qint16 getDx() { return dx; }
    qint16 getDy() { return dy; }
    qint16 getDz() { return dz; }

    void processLine() 
    {
        qint16 prevX = x;
        qint16 prevY = y;
        qint16 prevZ = z;

        // x y z
        // could be: 1234 -12 -987
        x = line.section(' ', 0, 0).toShort();
        y = line.section(' ', 1, 1).toShort();
        z = line.section(' ', 2, 2).toShort();

        dx = (x > prevX) ? x - prevX : prevX - x;
        dy = (y > prevY) ? y - prevY : prevY - y;
        dz = (z > prevZ) ? z - prevZ : prevZ - z;

        dx = ( (dx - NOISE) > 0) ? dx / 10 : 0;
        dy = ( (dy - NOISE) > 0) ? dy / 10 : 0;
        dz = ( (dz - NOISE) > 0) ? dz / 10 : 0;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    std::cout << "Connecting" << std::endl;
    if (client.connectTo("localhost", 6668)) {
        std::cout << "Connected!" << std::endl;

        client.sendMessage("Hello World");
        std::cout << "Text sent!" << std::endl;
        SensorData sensor("in.txt");
        for (int i = 0; i < 2000; ++i) {
            sensor.update();
            sensor.processLine();
            MyThread::msleep(100);
            client.sendMouseMovement(sensor.getDy(), sensor.getDz());
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
