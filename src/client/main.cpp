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

    qint64 dx;
    qint64 dy;
    qint64 dz;

    qint64 x;
    qint64 y;
    qint64 z;

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

    qint64 getDx() { return x; }
    qint64 getDy() { return y; }
    qint64 getDz() { return z; }

    void processLine()
    {
        // x y z
        // could be: 1234 -12 -987
        x += line.section(' ', 0, 0).toLong();
        y += line.section(' ', 1, 1).toLong();
        z = line.section(' ', 2, 2).toLong();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    std::cout << "Connecting" << std::endl;
    if (client.connectTo("koti.meelo.org", 6668)) {
        std::cout << "Connected!" << std::endl;

        //client.sendMessage("Hello World");
        //std::cout << "Text sent!" << std::endl;
        //SensorData sensor("in.txt");
        SensorData sensor("/sys/class/i2c-adapter/i2c-3/3-001d/coord");
        for (int i = 0; i < 2000; ++i) {
            sensor.update();
            sensor.processLine();
            MyThread::msleep(25);
            qint64 x = sensor.getDx() / 1000;
            qint64 y = sensor.getDy() / 1000;
            // z is roughly -1000 when it's laying on your hand, screen up.
            qint64 z = sensor.getDz() + 1000;

          //  if (x != 0 || z != 0) {
                qint16 dz = z > 0 ? 5 : -5;
                client.sendMouseMovement(0, dz );
                std::cout << x << ", " << y << ", " << z << std::endl;
            //}
            //std::cout << "Mouse movement sent!" << std::endl;
        }

        //client.sendClick(3);
        //std::cout << "Right mouse click sent!" << std::endl;

        //client.sendScroll(5);
        //std::cout << "Mouse wheel scroll sent!" << std::endl;
    }
    else {
        std::cout << "Connection failed :(" << std::endl;
    }
    return a.exec();
}
