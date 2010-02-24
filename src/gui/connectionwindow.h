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
    void terminateConnection(MouseWindow* mouseWindow)
    {
        for (std::size_t i = 0; i < mouseWindows.size(); ++i) {
            if (mouseWindows.at(i) == mouseWindow) {
                std::swap(mouseWindows.at(i), mouseWindows.back());
                mouseWindows.pop_back();
                mouseWindow->close();
                delete mouseWindow;
                mouseWindow = 0;
                break;
            }
        }
    }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConnectionWindow *m_ui;
    bool listChanged;
    std::vector<ServerData*> data;
    std::vector<MouseWindow*> mouseWindows;
//    MouseWindow *mouseWindow;
    void readList();

private slots:

private slots:
    void on_exitButton_clicked();
};

#endif // CONNECTIONWINDOW_H
