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

    qint16 getDx() { return x; }
    qint16 getDy() { return y; }
    qint16 getDz() { return z; }

    void processLine()
    {
        // x y z
        // could be: 1234 -12 -987
        x = line.section(' ', 0, 0).toLong();
        y = line.section(' ', 1, 1).toLong();
        z = line.section(' ', 2, 2).toLong();
    }
};
#endif // SENSORDATA_H
