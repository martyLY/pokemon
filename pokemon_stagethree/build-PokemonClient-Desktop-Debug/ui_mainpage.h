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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainpage
{
public:
    QListWidget *onlineList;
    QPushButton *matchBot;
    QPushButton *normalFightMatch;
    QPushButton *deadFightMatch;
    QPushButton *myInfo;

    void setupUi(QWidget *Mainpage)
    {
        if (Mainpage->objectName().isEmpty())
            Mainpage->setObjectName(QStringLiteral("Mainpage"));
        Mainpage->resize(634, 384);
        onlineList = new QListWidget(Mainpage);
        onlineList->setObjectName(QStringLiteral("onlineList"));
        onlineList->setGeometry(QRect(480, 20, 141, 351));
        matchBot = new QPushButton(Mainpage);
        matchBot->setObjectName(QStringLiteral("matchBot"));
        matchBot->setGeometry(QRect(20, 310, 98, 31));
        normalFightMatch = new QPushButton(Mainpage);
        normalFightMatch->setObjectName(QStringLiteral("normalFightMatch"));
        normalFightMatch->setGeometry(QRect(290, 30, 131, 31));
        deadFightMatch = new QPushButton(Mainpage);
        deadFightMatch->setObjectName(QStringLiteral("deadFightMatch"));
        deadFightMatch->setGeometry(QRect(290, 90, 131, 31));
        myInfo = new QPushButton(Mainpage);
        myInfo->setObjectName(QStringLiteral("myInfo"));
        myInfo->setGeometry(QRect(10, 30, 101, 51));

        retranslateUi(Mainpage);

        QMetaObject::connectSlotsByName(Mainpage);
    } // setupUi

    void retranslateUi(QWidget *Mainpage)
    {
        Mainpage->setWindowTitle(QApplication::translate("Mainpage", "Form", nullptr));
        matchBot->setText(QApplication::translate("Mainpage", "match", nullptr));
        normalFightMatch->setText(QApplication::translate("Mainpage", "Normal Fight", nullptr));
        deadFightMatch->setText(QApplication::translate("Mainpage", "Dead Fight", nullptr));
        myInfo->setText(QApplication::translate("Mainpage", "my\n"
" information", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mainpage: public Ui_Mainpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
