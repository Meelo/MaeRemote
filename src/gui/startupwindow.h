#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QtGui/QDockWidget>
#include <QLineEdit>
#include <QString>
#include <QStringList>

#include <fstream>
#include <string>
#include <vector>

#include "serverdata.h"

namespace Ui {
	class StartupWindow;
}

class StartupWindow : public QDockWidget {
	Q_OBJECT
public:
	StartupWindow(QWidget *parent = 0);
	~StartupWindow();

public slots:
	void addServerToList();
	void deleteServerFromList(int position);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::StartupWindow *m_ui;
	std::vector<ServerData*> data;
	void readList();
	void renderList();
};

#endif // STARTUPWINDOW_H
