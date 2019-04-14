#include "playerinfo.h"
#include "ui_playerinfo.h"

PlayerInfo::PlayerInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
}

PlayerInfo::~PlayerInfo()
{
    delete ui;
}
