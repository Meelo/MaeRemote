#include "serverdata.h"

ServerData::ServerData(QListWidget *parent, int type) : QListWidgetItem(parent,type), name(""), port(0)
{}

QString ServerData::getName()
{
    return name;
}

int ServerData::getPort()
{
    return port;
}

void ServerData::setName(QString name)
{
    this->name = name;
    this->setText(name + " : " + QString::number(port,10));
}

void ServerData::setPort(int port)
{
    this->port = port;
    this->setText(name + " : " + QString::number(port,10));
}
