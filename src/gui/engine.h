#ifndef ENGINE_H
#define ENGINE_H
#include <QThread>
#include <QString>
#include "client.h"

class Engine : public QThread
{
    QString host;
    Client* client;
    int port;
    bool connectionTerminated;
    bool locked;

public:
    Engine() : host("localhost"), client(0), port(6668), connectionTerminated(false), locked(false) { }
    ~Engine() { delete client; }
    void setHost(const QString& newHost) { host = newHost; }
    void setPort(int port) { this->port = port; }
    void run();
    void sendClick(qint16 button) { client->sendClick(button); }
    void sendScroll(qint16 delta) { client->sendScroll(delta); }
    void terminateConnection() { connectionTerminated = true; }
    void toggleLocked() { locked = !locked; }
    bool isLocked() const { return locked; }

    static void msleep(unsigned long msecs) { QThread::msleep(msecs); }
};

#endif // ENGINE_H
