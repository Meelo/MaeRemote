/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
<<<<<<< HEAD
** Created: Mon Feb 22 20:02:23 2010
**      by: Qt User Interface Compiler version 4.5.3
=======
** Created: Mon Feb 22 19:24:33 2010
**      by: Qt User Interface Compiler version 4.5.1
>>>>>>> eb883de2bc8e5dcbed66f0429b724cda7fffc365
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *rightMouseButton;
    QPushButton *leftMouseButton;
    QPushButton *lockButton;
    QPushButton *toggleButton;
    QFrame *scrollFrame;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        rightMouseButton = new QPushButton(centralWidget);
        rightMouseButton->setObjectName(QString::fromUtf8("rightMouseButton"));
        rightMouseButton->setGeometry(QRect(10, 10, 341, 161));
        leftMouseButton = new QPushButton(centralWidget);
        leftMouseButton->setObjectName(QString::fromUtf8("leftMouseButton"));
        leftMouseButton->setGeometry(QRect(10, 290, 341, 171));
        lockButton = new QPushButton(centralWidget);
        lockButton->setObjectName(QString::fromUtf8("lockButton"));
        lockButton->setGeometry(QRect(640, 340, 141, 121));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8("freeze.png")), QIcon::Normal, QIcon::On);
        lockButton->setIcon(icon);
        lockButton->setIconSize(QSize(110, 110));
        toggleButton = new QPushButton(centralWidget);
        toggleButton->setObjectName(QString::fromUtf8("toggleButton"));
        toggleButton->setGeometry(QRect(640, 10, 141, 121));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8("openlock_small.png")), QIcon::Normal, QIcon::On);
        toggleButton->setIcon(icon1);
        toggleButton->setIconSize(QSize(100, 100));
        scrollFrame = new QFrame(centralWidget);
        scrollFrame->setObjectName(QString::fromUtf8("scrollFrame"));
        scrollFrame->setGeometry(QRect(10, 180, 781, 101));
        scrollFrame->setFrameShape(QFrame::StyledPanel);
        scrollFrame->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(rightMouseButton, SIGNAL(clicked()), MainWindow, SLOT(rightMouseButtonClicked()));
        QObject::connect(leftMouseButton, SIGNAL(clicked()), MainWindow, SLOT(leftMouseButtonClicked()));
        QObject::connect(toggleButton, SIGNAL(clicked()), MainWindow, SLOT(toggleButtonClicked()));
        QObject::connect(lockButton, SIGNAL(pressed()), MainWindow, SLOT(lockButtonPressed()));
        QObject::connect(lockButton, SIGNAL(released()), MainWindow, SLOT(lockButtonReleased()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        rightMouseButton->setText(QString());
        leftMouseButton->setText(QString());
        lockButton->setText(QString());
        toggleButton->setText(QString());
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
