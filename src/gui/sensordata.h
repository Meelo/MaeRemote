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
#endif // SENSORDATA_H
