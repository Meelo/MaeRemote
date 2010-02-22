#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QAbstractItemView>

#include <fstream>
#include <string>
#include <vector>

#include "serverdata.h"
#include "engine.h"
#include "mousewindow.h"

namespace Ui {
    class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow {
    Q_OBJECT
public:
    ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();

public slots:
    void addServerToList();
    void deleteServerFromList();
    void connectToServer();
    void terminateConnection() { delete mouseWindow; mouseWindow = 0; }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConnectionWindow *m_ui;
    bool listChanged;
    std::vector<ServerData*> data;
    MouseWindow *mouseWindow;
    void readList();

private slots:
};

#endif // CONNECTIONWINDOW_H
