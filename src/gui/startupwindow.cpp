#include "startupwindow.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent) : QDockWidget(parent), m_ui(new Ui::StartupWindow)
{
	m_ui->setupUi(this);
	m_ui->portEdit->setText("6668");
	readList();
	renderList();
}

void StartupWindow::changeEvent(QEvent *e)
{
	QDockWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void StartupWindow::readList()
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
	}
}

void StartupWindow::renderList()
{
	m_ui->serverList->clear();
	for (int i = 0; i < data.size(); ++i) {
		m_ui->serverList->addItem(data.at(i));
	}
}

void StartupWindow::addServerToList()
{
	bool ok;
	int port = m_ui->portEdit->text().toInt(&ok, 10);
	if (ok && m_ui->addressEdit->text().length() > 0) {
		ServerData *sd = new ServerData(m_ui->serverList);
		sd->setName(m_ui->addressEdit->text());
		sd->setPort(port);
		data.push_back(sd);
		m_ui->addressEdit->setText("");
		renderList();
	}
}

void StartupWindow::deleteServerFromList(int position)
{

}

StartupWindow::~StartupWindow()
{
	delete m_ui;
	while (!data.empty()) {
		delete data.back();
		data.pop_back();
	}
}
