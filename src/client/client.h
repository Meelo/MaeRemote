#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    //Q_OBJECT

public:
    Client();
    void connectTo(const QString& hostName, quint16 port);
private slots:

private:
    QTcpSocket *tcpSocket;
};

#endif
