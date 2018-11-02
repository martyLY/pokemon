#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QWidget *parent) :
    QWidget(parent), mainpageUi(new Ui::Mainpage)
{
    mainpageUi->setupUi(this);
}

Mainpage::~Mainpage() {
    delete mainpageUi;
}
