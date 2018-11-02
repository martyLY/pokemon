#include "signuppage.h"
#include "ui_signuppage.h"

SignupPage::SignupPage(QWidget *parent) :
    QWidget(parent),
    signuppageUi(new Ui::SignupPage)
{
    signuppageUi->setupUi(this);
}
