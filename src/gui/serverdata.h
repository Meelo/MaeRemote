#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

class ServerData : public QListWidgetItem
{
	QString name;
	int port;

public:
	ServerData(QListWidget *parent = 0, int type = UserType);
	QString getName();
	int getPort();
	void setName(QString name);
	void setPort(int port);
};

#endif // SERVERDATA_H
