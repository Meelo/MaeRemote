#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    //Q_OBJECT

public:
    Client();
    bool connectTo(const QString& hostName, quint16 port);
    void send(const char* data, qint64 len);
    void sendMessage(const QByteArray& data);
    void sendMouseMovement(qint16 dx, qint16 dy);
    void sendClick(qint16 button);
    void sendScroll(qint16 amount);
private slots:
private:
    void send(const std::stringstream& block);
    QTcpSocket *tcpSocket;
    static const qint8 separator = 255;
};

#endif
