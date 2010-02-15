#include <QtNetwork>
#include "client.h"

Client::Client()
{
    tcpSocket = new QTcpSocket(this);
}

void Client::connectTo(const QString& hostName, quint16 port)
{
    tcpSocket->abort();
    tcpSocket->connectToHost(hostName, port);
}
