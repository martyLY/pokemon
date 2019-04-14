/********************************************************************************
** Form generated from reading UI file 'playerinfodetail.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERINFODETAIL_H
#define UI_PLAYERINFODETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerInfoDetail
{
public:
    QLabel *uiddisplay;
    QLabel *nicknamedisplay;
    QLabel *pokemoncountdisplay;
    QLabel *fightdisplay;
    QListWidget *pokemoninfolist;

    void setupUi(QWidget *PlayerInfoDetail)
    {
        if (PlayerInfoDetail->objectName().isEmpty())
            PlayerInfoDetail->setObjectName(QStringLiteral("PlayerInfoDetail"));
        PlayerInfoDetail->resize(480, 640);
        uiddisplay = new QLabel(PlayerInfoDetail);
        uiddisplay->setObjectName(QStringLiteral("uiddisplay"));
        uiddisplay->setGeometry(QRect(30, 40, 381, 23));
        nicknamedisplay = new QLabel(PlayerInfoDetail);
        nicknamedisplay->setObjectName(QStringLiteral("nicknamedisplay"));
        nicknamedisplay->setGeometry(QRect(30, 70, 381, 23));
        pokemoncountdisplay = new QLabel(PlayerInfoDetail);
        pokemoncountdisplay->setObjectName(QStringLiteral("pokemoncountdisplay"));
        pokemoncountdisplay->setGeometry(QRect(30, 100, 381, 23));
        fightdisplay = new QLabel(PlayerInfoDetail);
        fightdisplay->setObjectName(QStringLiteral("fightdisplay"));
        fightdisplay->setGeometry(QRect(30, 130, 381, 23));
        pokemoninfolist = new QListWidget(PlayerInfoDetail);
        pokemoninfolist->setObjectName(QStringLiteral("pokemoninfolist"));
        pokemoninfolist->setGeometry(QRect(30, 220, 411, 401));

        retranslateUi(PlayerInfoDetail);

        QMetaObject::connectSlotsByName(PlayerInfoDetail);
    } // setupUi

    void retranslateUi(QWidget *PlayerInfoDetail)
    {
        PlayerInfoDetail->setWindowTitle(QApplication::translate("PlayerInfoDetail", "Form", Q_NULLPTR));
        uiddisplay->setText(QApplication::translate("PlayerInfoDetail", "TextLabel", Q_NULLPTR));
        nicknamedisplay->setText(QApplication::translate("PlayerInfoDetail", "TextLabel", Q_NULLPTR));
        pokemoncountdisplay->setText(QApplication::translate("PlayerInfoDetail", "TextLabel", Q_NULLPTR));
        fightdisplay->setText(QApplication::translate("PlayerInfoDetail", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlayerInfoDetail: public Ui_PlayerInfoDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERINFODETAIL_H
