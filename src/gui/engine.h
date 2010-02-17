#ifndef ENGINE_H
#define ENGINE_H
#include <QThread>
#include <QString>
#include "client.h"

class Engine : public QThread
{
    QString host;
    Client* client;
public:
    Engine() : host("localhost"), client(0) { }
    ~Engine() { delete client; }
    void setHost(const QString& newHost) { host = newHost; }
    void run();
    void sendClick(qint16 button) { client->sendClick(button); }
    void sendScroll(qint16 delta) { client->sendScroll(delta); }

    static void msleep(unsigned long msecs) { QThread::msleep(msecs); }
};

#endif // ENGINE_H
