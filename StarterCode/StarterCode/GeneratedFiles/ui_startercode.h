/********************************************************************************
** Form generated from reading UI file 'startercode.ui'
**
** Created: Mon Dec 9 03:47:39 2013
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTERCODE_H
#define UI_STARTERCODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_StarterCodeClass
{
public:
    QWidget *centralWidget;
    MyGLWidget *widget;

    void setupUi(QMainWindow *StarterCodeClass)
    {
        if (StarterCodeClass->objectName().isEmpty())
            StarterCodeClass->setObjectName(QString::fromUtf8("StarterCodeClass"));
        StarterCodeClass->resize(659, 499);
        centralWidget = new QWidget(StarterCodeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 641, 481));
        StarterCodeClass->setCentralWidget(centralWidget);

        retranslateUi(StarterCodeClass);

        QMetaObject::connectSlotsByName(StarterCodeClass);
    } // setupUi

    void retranslateUi(QMainWindow *StarterCodeClass)
    {
        StarterCodeClass->setWindowTitle(QApplication::translate("StarterCodeClass", "StarterCode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StarterCodeClass: public Ui_StarterCodeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTERCODE_H
