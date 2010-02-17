#ifndef ENGINE_H
#define ENGINE_H
#include <QThread>
#include <QString>
#include "client.h"

class Engine : public QThread
{
    QString host;
public:
    Engine() : host("localhost") { }
    void setHost(const QString& newHost) { host = newHost; }
    void run();

    static void msleep(unsigned long msecs) { QThread::msleep(msecs); }
};

#endif // ENGINE_H
