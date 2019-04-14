/********************************************************************************
** Form generated from reading UI file 'fightpage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHTPAGE_H
#define UI_FIGHTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Fightpage
{
public:
    QPushButton *pushButton;
    QFrame *blueside;
    QLabel *blue;
    QFrame *line;
    QLabel *label;
    QLabel *blueNickname;
    QLabel *label_2;
    QLabel *bluePokemonName;
    QLabel *label_3;
    QLabel *blueLevel;
    QLabel *label_4;
    QLabel *blueRace;
    QLabel *label_5;
    QLabel *blueRarity;
    QLabel *label_6;
    QLabel *blueBaseAttack;
    QLabel *label_7;
    QLabel *blueDefense;
    QLabel *label_8;
    QLabel *blueWsp;
    QProgressBar *blueHp;
    QFrame *redside;
    QLabel *redNickname;
    QLabel *label_10;
    QLabel *redPokemonName;
    QLabel *label_11;
    QLabel *redLevel;
    QLabel *label_12;
    QLabel *redRace;
    QLabel *label_13;
    QLabel *redRarity;
    QLabel *label_14;
    QLabel *redBaseAttack;
    QLabel *label_15;
    QLabel *redDefense;
    QLabel *label_16;
    QLabel *redWsp;
    QLabel *label_9;
    QFrame *line_2;
    QLabel *blue_2;
    QProgressBar *redHp;
    QTextBrowser *bluefightinfo;
    QLabel *label_31;
    QTextBrowser *redfightinfo;

    void setupUi(QWidget *Fightpage)
    {
        if (Fightpage->objectName().isEmpty())
            Fightpage->setObjectName(QStringLiteral("Fightpage"));
        Fightpage->resize(957, 552);
        pushButton = new QPushButton(Fightpage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(370, 280, 98, 31));
        blueside = new QFrame(Fightpage);
        blueside->setObjectName(QStringLiteral("blueside"));
        blueside->setGeometry(QRect(0, 0, 961, 111));
        blueside->setFrameShape(QFrame::StyledPanel);
        blueside->setFrameShadow(QFrame::Raised);
        blue = new QLabel(blueside);
        blue->setObjectName(QStringLiteral("blue"));
        blue->setGeometry(QRect(20, 30, 101, 51));
        QFont font;
        font.setPointSize(25);
        blue->setFont(font);
        line = new QFrame(blueside);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(120, 0, 20, 121));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(blueside);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 10, 71, 23));
        blueNickname = new QLabel(blueside);
        blueNickname->setObjectName(QStringLiteral("blueNickname"));
        blueNickname->setGeometry(QRect(220, 10, 131, 23));
        label_2 = new QLabel(blueside);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 10, 121, 23));
        bluePokemonName = new QLabel(blueside);
        bluePokemonName->setObjectName(QStringLiteral("bluePokemonName"));
        bluePokemonName->setGeometry(QRect(530, 10, 161, 23));
        label_3 = new QLabel(blueside);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(390, 40, 61, 23));
        blueLevel = new QLabel(blueside);
        blueLevel->setObjectName(QStringLiteral("blueLevel"));
        blueLevel->setGeometry(QRect(450, 40, 81, 23));
        label_4 = new QLabel(blueside);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(390, 70, 74, 23));
        blueRace = new QLabel(blueside);
        blueRace->setObjectName(QStringLiteral("blueRace"));
        blueRace->setGeometry(QRect(450, 70, 74, 23));
        label_5 = new QLabel(blueside);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(560, 40, 61, 23));
        blueRarity = new QLabel(blueside);
        blueRarity->setObjectName(QStringLiteral("blueRarity"));
        blueRarity->setGeometry(QRect(630, 40, 74, 23));
        label_6 = new QLabel(blueside);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(560, 70, 74, 23));
        blueBaseAttack = new QLabel(blueside);
        blueBaseAttack->setObjectName(QStringLiteral("blueBaseAttack"));
        blueBaseAttack->setGeometry(QRect(630, 70, 74, 23));
        label_7 = new QLabel(blueside);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(730, 40, 74, 23));
        blueDefense = new QLabel(blueside);
        blueDefense->setObjectName(QStringLiteral("blueDefense"));
        blueDefense->setGeometry(QRect(820, 40, 74, 23));
        label_8 = new QLabel(blueside);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(730, 70, 74, 23));
        blueWsp = new QLabel(blueside);
        blueWsp->setObjectName(QStringLiteral("blueWsp"));
        blueWsp->setGeometry(QRect(820, 70, 74, 23));
        blueHp = new QProgressBar(blueside);
        blueHp->setObjectName(QStringLiteral("blueHp"));
        blueHp->setGeometry(QRect(150, 60, 201, 31));
        blueHp->setValue(24);
        redside = new QFrame(Fightpage);
        redside->setObjectName(QStringLiteral("redside"));
        redside->setGeometry(QRect(0, 440, 961, 111));
        redside->setFrameShape(QFrame::StyledPanel);
        redside->setFrameShadow(QFrame::Raised);
        redNickname = new QLabel(redside);
        redNickname->setObjectName(QStringLiteral("redNickname"));
        redNickname->setGeometry(QRect(600, 10, 131, 23));
        label_10 = new QLabel(redside);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 10, 121, 23));
        redPokemonName = new QLabel(redside);
        redPokemonName->setObjectName(QStringLiteral("redPokemonName"));
        redPokemonName->setGeometry(QRect(190, 10, 161, 23));
        label_11 = new QLabel(redside);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 40, 61, 23));
        redLevel = new QLabel(redside);
        redLevel->setObjectName(QStringLiteral("redLevel"));
        redLevel->setGeometry(QRect(80, 40, 81, 23));
        label_12 = new QLabel(redside);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 70, 71, 23));
        redRace = new QLabel(redside);
        redRace->setObjectName(QStringLiteral("redRace"));
        redRace->setGeometry(QRect(80, 70, 74, 23));
        label_13 = new QLabel(redside);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(190, 40, 61, 23));
        redRarity = new QLabel(redside);
        redRarity->setObjectName(QStringLiteral("redRarity"));
        redRarity->setGeometry(QRect(260, 40, 74, 23));
        label_14 = new QLabel(redside);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(190, 70, 74, 23));
        redBaseAttack = new QLabel(redside);
        redBaseAttack->setObjectName(QStringLiteral("redBaseAttack"));
        redBaseAttack->setGeometry(QRect(260, 70, 74, 23));
        label_15 = new QLabel(redside);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(360, 40, 74, 23));
        redDefense = new QLabel(redside);
        redDefense->setObjectName(QStringLiteral("redDefense"));
        redDefense->setGeometry(QRect(450, 40, 74, 23));
        label_16 = new QLabel(redside);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(360, 70, 74, 23));
        redWsp = new QLabel(redside);
        redWsp->setObjectName(QStringLiteral("redWsp"));
        redWsp->setGeometry(QRect(450, 70, 74, 23));
        label_9 = new QLabel(redside);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(530, 10, 71, 23));
        line_2 = new QFrame(redside);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(780, 0, 16, 111));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        blue_2 = new QLabel(redside);
        blue_2->setObjectName(QStringLiteral("blue_2"));
        blue_2->setGeometry(QRect(830, 30, 101, 51));
        blue_2->setFont(font);
        redHp = new QProgressBar(redside);
        redHp->setObjectName(QStringLiteral("redHp"));
        redHp->setGeometry(QRect(550, 60, 201, 31));
        redHp->setValue(24);
        bluefightinfo = new QTextBrowser(Fightpage);
        bluefightinfo->setObjectName(QStringLiteral("bluefightinfo"));
        bluefightinfo->setGeometry(QRect(10, 170, 241, 251));
        label_31 = new QLabel(Fightpage);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(20, 130, 211, 23));
        redfightinfo = new QTextBrowser(Fightpage);
        redfightinfo->setObjectName(QStringLiteral("redfightinfo"));
        redfightinfo->setGeometry(QRect(710, 170, 241, 251));

        retranslateUi(Fightpage);

        QMetaObject::connectSlotsByName(Fightpage);
    } // setupUi

    void retranslateUi(QWidget *Fightpage)
    {
        Fightpage->setWindowTitle(QApplication::translate("Fightpage", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Fightpage", "PushButton", Q_NULLPTR));
        blue->setText(QApplication::translate("Fightpage", "BLUE", Q_NULLPTR));
        label->setText(QApplication::translate("Fightpage", "Master:", Q_NULLPTR));
        blueNickname->setText(QString());
        label_2->setText(QApplication::translate("Fightpage", "Pokemon Name:", Q_NULLPTR));
        bluePokemonName->setText(QString());
        label_3->setText(QApplication::translate("Fightpage", "Level:", Q_NULLPTR));
        blueLevel->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("Fightpage", "Race:", Q_NULLPTR));
        blueRace->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("Fightpage", "Rarity:", Q_NULLPTR));
        blueRarity->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("Fightpage", "Attack:", Q_NULLPTR));
        blueBaseAttack->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_7->setText(QApplication::translate("Fightpage", "Defense:", Q_NULLPTR));
        blueDefense->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_8->setText(QApplication::translate("Fightpage", "Wsp:", Q_NULLPTR));
        blueWsp->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        redNickname->setText(QString());
        label_10->setText(QApplication::translate("Fightpage", "Pokemon Name:", Q_NULLPTR));
        redPokemonName->setText(QString());
        label_11->setText(QApplication::translate("Fightpage", "Level:", Q_NULLPTR));
        redLevel->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_12->setText(QApplication::translate("Fightpage", "Race:", Q_NULLPTR));
        redRace->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_13->setText(QApplication::translate("Fightpage", "Rarity:", Q_NULLPTR));
        redRarity->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_14->setText(QApplication::translate("Fightpage", "Attack:", Q_NULLPTR));
        redBaseAttack->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_15->setText(QApplication::translate("Fightpage", "Defense:", Q_NULLPTR));
        redDefense->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_16->setText(QApplication::translate("Fightpage", "Wsp:", Q_NULLPTR));
        redWsp->setText(QApplication::translate("Fightpage", "TextLabel", Q_NULLPTR));
        label_9->setText(QApplication::translate("Fightpage", "Master:", Q_NULLPTR));
        blue_2->setText(QApplication::translate("Fightpage", "RED", Q_NULLPTR));
        label_31->setText(QApplication::translate("Fightpage", "blue fight info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Fightpage: public Ui_Fightpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTPAGE_H
