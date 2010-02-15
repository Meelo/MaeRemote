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

void Client::sendMessage(const QByteArray& data)
{
    QByteArray block("M");
    block.append(separator).append(data);
    send(block.data(), block.size());
}

void Client::sendMouseMovement(qint16 dx, qint16 dy)
{
    std::stringstream block;
    block << 'U';
    block << separator;
    block << dx;
    block << separator;
    block << dy;
    const std::string& data = block.str();
    send(data.c_str(), data.length());
}

// The value of button corresponds to the mouse button pressed.
// Mouse1 = 1, Mouse2 = 2 and Mouse3 = 3.
void Client::sendClick(qint16 button)
{
    std::stringstream block;
    block << 'C';
    block << separator;
    block << button;
    send(block);
}

void Client::sendScroll(qint16 amount)
{
    std::stringstream block;
    block << 'S';
    block << separator;
    block << amount;
    send(block);
}

void Client::send(const std::stringstream& block)
{
    const std::string& data = block.str();
    send(data.c_str(), data.length());
}
