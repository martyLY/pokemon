/********************************************************************************
** Form generated from reading UI file 'playinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYINFO_H
#define UI_PLAYINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayInfo
{
public:
    QLabel *uiddisplay;
    QLabel *nicknamedisplay;

    void setupUi(QWidget *PlayInfo)
    {
        if (PlayInfo->objectName().isEmpty())
            PlayInfo->setObjectName(QStringLiteral("PlayInfo"));
        PlayInfo->resize(377, 87);
        uiddisplay = new QLabel(PlayInfo);
        uiddisplay->setObjectName(QStringLiteral("uiddisplay"));
        uiddisplay->setGeometry(QRect(20, 20, 311, 23));
        nicknamedisplay = new QLabel(PlayInfo);
        nicknamedisplay->setObjectName(QStringLiteral("nicknamedisplay"));
        nicknamedisplay->setGeometry(QRect(20, 50, 321, 23));

        retranslateUi(PlayInfo);

        QMetaObject::connectSlotsByName(PlayInfo);
    } // setupUi

    void retranslateUi(QWidget *PlayInfo)
    {
        PlayInfo->setWindowTitle(QApplication::translate("PlayInfo", "Form", nullptr));
        uiddisplay->setText(QApplication::translate("PlayInfo", "TextLabel", nullptr));
        nicknamedisplay->setText(QApplication::translate("PlayInfo", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayInfo: public Ui_PlayInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYINFO_H
