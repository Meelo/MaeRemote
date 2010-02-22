#ifndef SENSORDATA_H
#define SENSORDATA_H
#include <QByteArray>
#include <QTextStream>
#include <QFile>

class SensorData
{
    static const qint16 NOISE = 40;
    QString line;
    QFile file;

    quint64 counter;

    qint16 dx;
    qint16 dy;
    qint16 dz;

    qint16 x;
    qint16 y;
    qint16 z;

    qint16 oldx;
    qint16 oldy;
    qint16 oldz;

    public:
    SensorData(const QString& filename) : file(filename),
    counter(0), dx(0), dy(0), dz(0),
    x(0), y(0), z(0), oldx(0), oldy(0), oldz(0) {}

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

    qint16 getX() { return x; }
    qint16 getY() { return y; }
    qint16 getZ() { return z; }

    void processLine()
    {
        // x y z
        // could be: 1234 -12 -987
        x = line.section(' ', 0, 0).toLong();
        y = line.section(' ', 1, 1).toLong();
        z = line.section(' ', 2, 2).toLong();

        // Smoothen the data from sensor.
        if (counter > 0) {
            x = oldx + (x - oldx) * 0.1;
            y = oldy + (y - oldy) * 0.1;
            z = oldz + (z - oldz) * 0.1;
        }

        oldx = x;
        oldy = y;
        oldz = z;

        ++counter;
    }

    // Most likely used after a lock.
    // Used to start building speed from scratch,
    // so old values won't compromise new data.
    void reInitializeValues()
    {
        counter = 0;
        x = 0;
        y = 0;
        z = 0;
    }
};
#endif // SENSORDATA_H
