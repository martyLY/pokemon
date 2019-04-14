/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *startMenu;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *loginName;
    QLineEdit *loginPassword;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *signupButton;
    QLabel *errorinfo;

    void setupUi(QWidget *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName(QStringLiteral("StartMenu"));
        StartMenu->resize(648, 457);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StartMenu->sizePolicy().hasHeightForWidth());
        StartMenu->setSizePolicy(sizePolicy);
        StartMenu->setBaseSize(QSize(648, 457));
        startMenu = new QWidget(StartMenu);
        startMenu->setObjectName(QStringLiteral("startMenu"));
        startMenu->setGeometry(QRect(170, 160, 471, 171));
        gridLayoutWidget = new QWidget(startMenu);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 271, 81));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        loginName = new QLineEdit(gridLayoutWidget);
        loginName->setObjectName(QStringLiteral("loginName"));
        loginName->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        loginName->setText(QStringLiteral(""));

        gridLayout->addWidget(loginName, 0, 1, 1, 2);

        loginPassword = new QLineEdit(gridLayoutWidget);
        loginPassword->setObjectName(QStringLiteral("loginPassword"));

        gridLayout->addWidget(loginPassword, 1, 1, 1, 2);

        horizontalLayoutWidget = new QWidget(startMenu);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 120, 201, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loginButton = new QPushButton(horizontalLayoutWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));

        horizontalLayout->addWidget(loginButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        signupButton = new QPushButton(horizontalLayoutWidget);
        signupButton->setObjectName(QStringLiteral("signupButton"));

        horizontalLayout->addWidget(signupButton);

        errorinfo = new QLabel(startMenu);
        errorinfo->setObjectName(QStringLiteral("errorinfo"));
        errorinfo->setGeometry(QRect(50, 82, 361, 31));
        errorinfo->setStyleSheet(QStringLiteral("color: rgb(204, 0, 0);"));
        errorinfo->setTextFormat(Qt::PlainText);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QWidget *StartMenu)
    {
        StartMenu->setWindowTitle(QApplication::translate("StartMenu", "Form", Q_NULLPTR));
        loginName->setPlaceholderText(QApplication::translate("StartMenu", "Your Account", Q_NULLPTR));
        loginPassword->setInputMask(QString());
        loginPassword->setText(QString());
        loginPassword->setPlaceholderText(QApplication::translate("StartMenu", "Your Password", Q_NULLPTR));
        loginButton->setText(QApplication::translate("StartMenu", "Login ", Q_NULLPTR));
        signupButton->setText(QApplication::translate("StartMenu", "Sign up", Q_NULLPTR));
        errorinfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
