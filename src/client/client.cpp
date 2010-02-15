#include <sstream>
#include <QtNetwork>
#include "client.h"

Client::Client()
{
    tcpSocket = new QTcpSocket(this);
}

bool Client::connectTo(const QString& hostName, quint16 port)
{
    tcpSocket->abort();
    tcpSocket->connectToHost(hostName, port);
    return tcpSocket->waitForConnected(5000);
}

void Client::send(const char* data, qint64 len)
{
    tcpSocket->write(data, len);
    tcpSocket->write("\n", 1);
    tcpSocket->flush();
}

void Client::sendMouseMovement(qint16 dx, qint16 dy)
{
    std::stringstream block;
    block << 'U';
    block << separator;
    block << dx;
    block << separator;
    block << dy;
    const std::string& movement = block.str();
    send(movement.c_str(), movement.length());
}

void Client::sendMessage(const QByteArray& data)
{
    QByteArray block("M");
    block.append(separator).append(data);
    send(block.data(), block.size());
}


