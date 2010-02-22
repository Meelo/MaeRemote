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
#include "mainwindow.h"

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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConnectionWindow *m_ui;
    bool listChanged;
    std::vector<ServerData*> data;
    MainWindow *mainWindow;
    void readList();

private slots:
    void on_connectButton_clicked();
    void on_exitButton_clicked();
};

#endif // CONNECTIONWINDOW_H
