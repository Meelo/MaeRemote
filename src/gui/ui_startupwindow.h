/********************************************************************************
** Form generated from reading ui file 'startupwindow.ui'
**
** Created: Thu Feb 18 20:57:46 2010
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STARTUPWINDOW_H
#define UI_STARTUPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartupWindow
{
public:
    QWidget *dockWidgetContents;
    QPushButton *connectButton;
    QPushButton *addButton;
    QLineEdit *addressEdit;
    QLabel *label;
    QLineEdit *portEdit;
    QLabel *label_2;
    QListWidget *serverList;
    QPushButton *deleteButton;
    QPushButton *exitButton;

    void setupUi(QDockWidget *StartupWindow)
    {
        if (StartupWindow->objectName().isEmpty())
            StartupWindow->setObjectName(QString::fromUtf8("StartupWindow"));
        StartupWindow->resize(800, 400);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        connectButton = new QPushButton(dockWidgetContents);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(480, 310, 121, 61));
        addButton = new QPushButton(dockWidgetContents);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(690, 60, 101, 61));
        addressEdit = new QLineEdit(dockWidgetContents);
        addressEdit->setObjectName(QString::fromUtf8("addressEdit"));
        addressEdit->setGeometry(QRect(30, 20, 641, 20));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 0, 141, 16));
        portEdit = new QLineEdit(dockWidgetContents);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));
        portEdit->setGeometry(QRect(690, 20, 101, 20));
        portEdit->setMaxLength(5);
        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(690, 0, 61, 16));
        serverList = new QListWidget(dockWidgetContents);
        serverList->setObjectName(QString::fromUtf8("serverList"));
        serverList->setGeometry(QRect(30, 60, 641, 241));
        deleteButton = new QPushButton(dockWidgetContents);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(690, 140, 101, 61));
        exitButton = new QPushButton(dockWidgetContents);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(194, 310, 121, 61));
        StartupWindow->setWidget(dockWidgetContents);

        retranslateUi(StartupWindow);
        QObject::connect(deleteButton, SIGNAL(clicked()), serverList, SLOT(clear()));
        QObject::connect(addButton, SIGNAL(clicked()), StartupWindow, SLOT(addServerToList()));

        QMetaObject::connectSlotsByName(StartupWindow);
    } // setupUi

    void retranslateUi(QDockWidget *StartupWindow)
    {
        StartupWindow->setWindowTitle(QApplication::translate("StartupWindow", "MaeRemote", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("StartupWindow", "Connect", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("StartupWindow", "Add", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StartupWindow", "Server IP-address, or name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StartupWindow", "Server port", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("StartupWindow", "Remove", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("StartupWindow", "Exit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StartupWindow);
    } // retranslateUi

};

namespace Ui {
    class StartupWindow: public Ui_StartupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPWINDOW_H
