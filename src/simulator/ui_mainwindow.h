/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnCreateEntityRelation;
    QPushButton *btnReadEntity;
    QPushButton *btnCreateClassInheritance;
    QPushButton *btnOpenCloseGraph;
    QPushButton *btnReadClassInheritance;
    QPushButton *btnGenerateMap;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnCreateEntityRelation = new QPushButton(centralwidget);
        btnCreateEntityRelation->setObjectName(QString::fromUtf8("btnCreateEntityRelation"));
        btnCreateEntityRelation->setGeometry(QRect(10, 10, 201, 26));
        btnReadEntity = new QPushButton(centralwidget);
        btnReadEntity->setObjectName(QString::fromUtf8("btnReadEntity"));
        btnReadEntity->setGeometry(QRect(10, 40, 201, 26));
        btnCreateClassInheritance = new QPushButton(centralwidget);
        btnCreateClassInheritance->setObjectName(QString::fromUtf8("btnCreateClassInheritance"));
        btnCreateClassInheritance->setGeometry(QRect(10, 70, 191, 26));
        btnOpenCloseGraph = new QPushButton(centralwidget);
        btnOpenCloseGraph->setObjectName(QString::fromUtf8("btnOpenCloseGraph"));
        btnOpenCloseGraph->setGeometry(QRect(10, 130, 191, 26));
        btnReadClassInheritance = new QPushButton(centralwidget);
        btnReadClassInheritance->setObjectName(QString::fromUtf8("btnReadClassInheritance"));
        btnReadClassInheritance->setGeometry(QRect(10, 100, 191, 26));
        btnGenerateMap = new QPushButton(centralwidget);
        btnGenerateMap->setObjectName(QString::fromUtf8("btnGenerateMap"));
        btnGenerateMap->setGeometry(QRect(270, 10, 121, 26));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnCreateEntityRelation->setText(QCoreApplication::translate("MainWindow", "Create Entities && Relation", nullptr));
        btnReadEntity->setText(QCoreApplication::translate("MainWindow", "Read Entities", nullptr));
        btnCreateClassInheritance->setText(QCoreApplication::translate("MainWindow", "Create Classes && Inheritance", nullptr));
        btnOpenCloseGraph->setText(QCoreApplication::translate("MainWindow", "Open && Close Graph", nullptr));
        btnReadClassInheritance->setText(QCoreApplication::translate("MainWindow", "Read Classes && Inheritance", nullptr));
        btnGenerateMap->setText(QCoreApplication::translate("MainWindow", "Generate Map", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
