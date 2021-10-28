/********************************************************************************
** Form generated from reading UI file 'untitled.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UNTITLED_H
#define UNTITLED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
  QWidget *centralwidget;
  QPushButton *pushButton;
  QLCDNumber *lcdNumber;
  QSlider *horizontalSlider;
  QMenuBar *menubar;
  QMenu *menuTest;
  QStatusBar *statusbar;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(800, 600);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(220, 430, 301, 25));
    pushButton->setMouseTracking(true);
    pushButton->setFlat(false);
    lcdNumber = new QLCDNumber(centralwidget);
    lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
    lcdNumber->setGeometry(QRect(370, 250, 171, 81));
    horizontalSlider = new QSlider(centralwidget);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setGeometry(QRect(220, 460, 311, 41));
    horizontalSlider->setOrientation(Qt::Horizontal);
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 22));
    menuTest = new QMenu(menubar);
    menuTest->setObjectName(QString::fromUtf8("menuTest"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuTest->menuAction());

    retranslateUi(MainWindow);
    QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));

    pushButton->setDefault(true);


    QMetaObject::connectSlotsByName(MainWindow);
  }// setupUi

  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    pushButton->setText(QApplication::translate("MainWindow", "CASH FLOW BABY", nullptr));
    menuTest->setTitle(QApplication::translate("MainWindow", "Test", nullptr));
  }// retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow
{
};
}// namespace Ui

QT_END_NAMESPACE

#endif// UNTITLED_H
