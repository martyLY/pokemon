/********************************************************************************
** Form generated from reading UI file 'signuppage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPPAGE_H
#define UI_SIGNUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignupPage
{
public:
    QLineEdit *signupAccount;
    QLineEdit *signupPassword;
    QLineEdit *signupPasswordConfirm;
    QLineEdit *pokemonName;
    QPushButton *generatePokemon;
    QPushButton *back;
    QLabel *errorinfo;
    QLineEdit *signupNickName;

    void setupUi(QWidget *SignupPage)
    {
        if (SignupPage->objectName().isEmpty())
            SignupPage->setObjectName(QStringLiteral("SignupPage"));
        SignupPage->resize(687, 483);
        signupAccount = new QLineEdit(SignupPage);
        signupAccount->setObjectName(QStringLiteral("signupAccount"));
        signupAccount->setGeometry(QRect(210, 50, 191, 24));
        signupPassword = new QLineEdit(SignupPage);
        signupPassword->setObjectName(QStringLiteral("signupPassword"));
        signupPassword->setGeometry(QRect(210, 130, 191, 24));
        signupPasswordConfirm = new QLineEdit(SignupPage);
        signupPasswordConfirm->setObjectName(QStringLiteral("signupPasswordConfirm"));
        signupPasswordConfirm->setGeometry(QRect(210, 170, 191, 24));
        pokemonName = new QLineEdit(SignupPage);
        pokemonName->setObjectName(QStringLiteral("pokemonName"));
        pokemonName->setGeometry(QRect(210, 210, 191, 24));
        generatePokemon = new QPushButton(SignupPage);
        generatePokemon->setObjectName(QStringLiteral("generatePokemon"));
        generatePokemon->setGeometry(QRect(210, 290, 191, 31));
        back = new QPushButton(SignupPage);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(40, 30, 98, 31));
        errorinfo = new QLabel(SignupPage);
        errorinfo->setObjectName(QStringLiteral("errorinfo"));
        errorinfo->setGeometry(QRect(210, 250, 361, 23));
        errorinfo->setStyleSheet(QStringLiteral("color: rgb(204, 0, 0);"));
        signupNickName = new QLineEdit(SignupPage);
        signupNickName->setObjectName(QStringLiteral("signupNickName"));
        signupNickName->setGeometry(QRect(210, 90, 191, 24));

        retranslateUi(SignupPage);

        QMetaObject::connectSlotsByName(SignupPage);
    } // setupUi

    void retranslateUi(QWidget *SignupPage)
    {
        SignupPage->setWindowTitle(QApplication::translate("SignupPage", "Form", Q_NULLPTR));
        signupAccount->setPlaceholderText(QApplication::translate("SignupPage", "Your Account", Q_NULLPTR));
        signupPassword->setPlaceholderText(QApplication::translate("SignupPage", "Your Password", Q_NULLPTR));
        signupPasswordConfirm->setPlaceholderText(QApplication::translate("SignupPage", "Confirm your password", Q_NULLPTR));
        pokemonName->setPlaceholderText(QApplication::translate("SignupPage", "Your Pokemon Name", Q_NULLPTR));
        generatePokemon->setText(QApplication::translate("SignupPage", "\347\224\237\346\210\220", Q_NULLPTR));
        back->setText(QApplication::translate("SignupPage", "\350\277\224\345\233\236", Q_NULLPTR));
        errorinfo->setText(QString());
        signupNickName->setText(QString());
        signupNickName->setPlaceholderText(QApplication::translate("SignupPage", "Your NickName", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignupPage: public Ui_SignupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPPAGE_H
