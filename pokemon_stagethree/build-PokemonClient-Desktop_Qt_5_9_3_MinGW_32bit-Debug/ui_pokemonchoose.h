/********************************************************************************
** Form generated from reading UI file 'pokemonchoose.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POKEMONCHOOSE_H
#define UI_POKEMONCHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pokemonChoose
{
public:
    QListWidget *pokemonToChoose;
    QPushButton *chooseOk;

    void setupUi(QWidget *pokemonChoose)
    {
        if (pokemonChoose->objectName().isEmpty())
            pokemonChoose->setObjectName(QStringLiteral("pokemonChoose"));
        pokemonChoose->resize(471, 190);
        pokemonToChoose = new QListWidget(pokemonChoose);
        pokemonToChoose->setObjectName(QStringLiteral("pokemonToChoose"));
        pokemonToChoose->setGeometry(QRect(10, 0, 451, 141));
        chooseOk = new QPushButton(pokemonChoose);
        chooseOk->setObjectName(QStringLiteral("chooseOk"));
        chooseOk->setGeometry(QRect(190, 150, 98, 31));

        retranslateUi(pokemonChoose);

        QMetaObject::connectSlotsByName(pokemonChoose);
    } // setupUi

    void retranslateUi(QWidget *pokemonChoose)
    {
        pokemonChoose->setWindowTitle(QApplication::translate("pokemonChoose", "Form", Q_NULLPTR));
        chooseOk->setText(QApplication::translate("pokemonChoose", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class pokemonChoose: public Ui_pokemonChoose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POKEMONCHOOSE_H
