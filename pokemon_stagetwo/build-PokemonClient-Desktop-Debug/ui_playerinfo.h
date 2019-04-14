/********************************************************************************
** Form generated from reading UI file 'playerinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERINFO_H
#define UI_PLAYERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerInfo
{
public:
    QLabel *uiddisplay;
    QLabel *nicknamedisplay;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *PlayerInfo)
    {
        if (PlayerInfo->objectName().isEmpty())
            PlayerInfo->setObjectName(QStringLiteral("PlayerInfo"));
        PlayerInfo->resize(269, 46);
        uiddisplay = new QLabel(PlayerInfo);
        uiddisplay->setObjectName(QStringLiteral("uiddisplay"));
        uiddisplay->setGeometry(QRect(60, 0, 251, 23));
        nicknamedisplay = new QLabel(PlayerInfo);
        nicknamedisplay->setObjectName(QStringLiteral("nicknamedisplay"));
        nicknamedisplay->setGeometry(QRect(100, 20, 261, 23));
        label = new QLabel(PlayerInfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 31, 23));
        label_2 = new QLabel(PlayerInfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 91, 23));

        retranslateUi(PlayerInfo);

        QMetaObject::connectSlotsByName(PlayerInfo);
    } // setupUi

    void retranslateUi(QWidget *PlayerInfo)
    {
        PlayerInfo->setWindowTitle(QApplication::translate("PlayerInfo", "Form", nullptr));
        uiddisplay->setText(QApplication::translate("PlayerInfo", "TextLabel", nullptr));
        nicknamedisplay->setText(QApplication::translate("PlayerInfo", "TextLabel", nullptr));
        label->setText(QApplication::translate("PlayerInfo", "Uid:", nullptr));
        label_2->setText(QApplication::translate("PlayerInfo", "Nickname:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerInfo: public Ui_PlayerInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERINFO_H
