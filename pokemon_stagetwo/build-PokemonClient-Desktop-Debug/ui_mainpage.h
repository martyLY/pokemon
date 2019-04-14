/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainpage
{
public:
    QListWidget *onlineList;

    void setupUi(QWidget *Mainpage)
    {
        if (Mainpage->objectName().isEmpty())
            Mainpage->setObjectName(QStringLiteral("Mainpage"));
        Mainpage->resize(630, 399);
        onlineList = new QListWidget(Mainpage);
        onlineList->setObjectName(QStringLiteral("onlineList"));
        onlineList->setGeometry(QRect(320, 20, 221, 351));

        retranslateUi(Mainpage);

        QMetaObject::connectSlotsByName(Mainpage);
    } // setupUi

    void retranslateUi(QWidget *Mainpage)
    {
        Mainpage->setWindowTitle(QApplication::translate("Mainpage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mainpage: public Ui_Mainpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
