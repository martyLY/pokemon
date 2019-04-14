#include "playerinfo.h"
#include "ui_playerinfo.h"
#include "ui_playerinfodetail.h"

PlayerInfo::PlayerInfo(QJsonDocument playerinfo ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
    //初始化简略信息显示
    ui->uiddisplay->setText(QString::number(playerinfo["uid"].toInt()));
    ui->nicknamedisplay->setText(playerinfo["nickname"].toString());
    uid = playerinfo["uid"].toInt();

    detail = new PlayerInfoDetail(playerinfo); //创建详细信息类并隐藏
    detail->hide();
}

PlayerInfo::~PlayerInfo()
{
    delete ui;
}

void PlayerInfo::showDetail() {
    detail->show();
}


/************************player's detail info***********************/

PlayerInfoDetail::PlayerInfoDetail(QJsonDocument playerinfodetail, QWidget *parent) :
    QWidget (parent),
    ui(new Ui::PlayerInfoDetail)
{
    ui->setupUi(this);

    //设置玩家基本信息
    QJsonObject playerinfo = playerinfodetail["usrinfo"].toObject();
    //qDebug()<<playerinfodetail<<endl;
    ui->uiddisplay->setText("uid: " + QString::number(playerinfo["uid"].toInt()));  //设置uid
    ui->nicknamedisplay->setText("nickname: "+playerinfo["nickname"].toString());  //设置昵称
    ui->pokemoncountdisplay->setText("pokemoncount: "+QString::number(playerinfo["pokemoncount"].toInt()));  //设置精灵数量
    ui->fightdisplay->setText("win/fight: "+QString::number(playerinfo["wincount"].toInt())+'/'+QString::number(playerinfo["fightcount"].toInt()));

    //设置玩家所有精灵详细信息
    QJsonArray pokemoninfolist = playerinfodetail["pokemoninfo"].toArray();
    //qDebug()<<QJsonDocument(pokemoninfolist[0].toObject()).toJson()<<endl;
    QJsonArray::iterator iter;

    //将每个精灵的信息添加到精灵显示列表
    for(iter = pokemoninfolist.begin(); iter != pokemoninfolist.end(); iter++){
        QLabel *label = new QLabel(QJsonDocument((*iter).toObject()).toJson());
        label->adjustSize();
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(label->size());
        ui->pokemoninfolist->addItem(item);
        ui->pokemoninfolist->setItemWidget(item, label);
    }

    setWindowFlags(Qt::WindowStaysOnTopHint); //窗口置顶
}

PlayerInfoDetail::~PlayerInfoDetail()
{
    delete  ui;
}
