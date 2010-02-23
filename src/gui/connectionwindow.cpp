#include "connectionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::ConnectionWindow),
    listChanged(false)
{
    m_ui->setupUi(this);
    m_ui->portEdit->setText("6668");
    m_ui->serverList->setSelectionMode(QAbstractItemView::MultiSelection);
    readList();
}

ConnectionWindow::~ConnectionWindow()
{
    delete m_ui;
    while (!data.empty()) {
        delete data.back();
        data.pop_back();
    }

    while (!mouseWindows.empty()) {
        MouseWindow* window = mouseWindows.back();
        window->close();
        delete window;
        mouseWindows.pop_back();
    }
}

void ConnectionWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ConnectionWindow::readList()
{
    std::string line;
    std::ifstream listFile;
    listFile.open("serverlist.txt");
    if (listFile.is_open()) {
        while (!listFile.eof()) {
            getline(listFile,line);
            QString str(line.c_str());
            QStringList strList = str.split(",");
            bool ok;
            if (strList.length() > 1) {
                int port = strList[1].toInt(&ok, 10);
                if (ok) {
                    ServerData *sd = new ServerData(m_ui->serverList);
                    sd->setName(strList[0]);
                    sd->setPort(port);
                    data.push_back(sd);
                }
            }
        }
        listFile.close();
    }
}

void ConnectionWindow::addServerToList()
{
    listChanged = true;
    bool ok;
    int port = m_ui->portEdit->text().toInt(&ok, 10);
    if (ok && m_ui->addressEdit->text().length() > 0) {
        ServerData *sd = new ServerData(m_ui->serverList);
        sd->setName(m_ui->addressEdit->text());
        sd->setPort(port);
        data.push_back(sd);
        m_ui->addressEdit->setText("");
    }
}

void ConnectionWindow::deleteServerFromList()
{
    listChanged = true;
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (data.at(i)->isSelected()) {
            delete data.at(i);
            data.erase(data.begin() +i );
        }
    }
}

void ConnectionWindow::connectToServer()
{
    bool ok;
    QString host = m_ui->addressEdit->text();
    int port = m_ui->portEdit->text().toInt(&ok, 10);
    if (!ok || m_ui->addressEdit->text().length() < 1) {
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (data.at(i)->isSelected()) {
                host = data.at(i)->getName();
                port = data.at(i)->getPort();
                break;
            }
        }
    }

    Engine *engine = new Engine();
    engine->setHost(host);
    engine->setPort(port);

    MouseWindow *mouseWindow = new MouseWindow(this);
    mouseWindows.push_back(mouseWindow);
    mouseWindow->setAttribute(Qt::WA_DeleteOnClose, true);
    mouseWindow->setEngine(engine);

// use fullscreen on Maemo5, otherwise windowed..
#ifdef __ARMEL__
    mouseWindow->showFullScreen();
#else
    mouseWindow->show();
#endif

    engine->start();
    if (listChanged) {
        std::ofstream listFile;
        listFile.open("serverlist.txt");
        if (listFile.is_open()) {
            for (std::size_t i = 0; i < data.size(); ++i) {
                listFile << data.at(i)->getName().toStdString() << "," << data.at(i)->getPort() << std::endl;
            }
            listFile.close();
        }
    }            
}

void ConnectionWindow::on_exitButton_clicked()
{
    while (!mouseWindows.empty()) {
        MouseWindow* window = mouseWindows.back();
        window->close();
    }
    exit(0);
}
