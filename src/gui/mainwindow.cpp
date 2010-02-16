#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	Scroll *scroll = new Scroll(ui->scrollFrame);
	scroll->setMainWindow(this);
	locked = false;
	tempLocked = false;
}

void MainWindow::processScrollBarActivity(int delta)
{
	if (!locked && !tempLocked) {
		qDebug() << delta;
	}
}

void MainWindow::leftMouseButtonClicked()
{
	qDebug() << "Left button clicked";
}

void MainWindow::rightMouseButtonClicked()
{
	qDebug() << "Right button clicked";
}

void MainWindow::toggleButtonClicked()
{
	locked = !locked;
	qDebug() << locked;
}

void MainWindow::lockButtonPressed()
{
	tempLocked = true;
	qDebug() << tempLocked;
}

void MainWindow::lockButtonReleased()
{
	tempLocked =false;
	qDebug() << tempLocked;
}

MainWindow::~MainWindow()
{
    delete ui;
}
