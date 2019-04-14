#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QUdpSocket *socket, QWidget *parent) :
    QWidget(parent), usrSocket(socket), mainpageUi(new Ui::Mainpage)
{
    mainpageUi->setupUi(this);
    mainpageUi->onlineList->setResizeMode(QListWidget::Adjust);  //在线用户列表设置成适应文本宽度模式

    //双击在线用户信号,双击后显示详细用户信息
    connect(mainpageUi->onlineList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
             this, SLOT(showPlayerInfoDetail(QListWidgetItem *)));
}

Mainpage::~Mainpage() {
    delete mainpageUi;
}

void Mainpage::setOtherUsrInfo(QJsonDocument dataJson) {
   //添加一名在线用户信息到列表
    PlayerInfo *playinfo = new PlayerInfo(dataJson);
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(playinfo->size());
    mainpageUi->onlineList->addItem(item);
    mainpageUi->onlineList->setItemWidget(item, playinfo);

    onlineUsr_map[playinfo->getUid()] = item;

    //debug输出
    qDebug()<<mainpageUi->onlineList->count()<<endl;
    qDebug()<<mainpageUi->onlineList<<endl;
    qDebug()<<onlineUsr_map<<endl;
    qDebug()<<"item:"<<item<<endl;
    qDebug()<<"play:"<<playinfo<<endl;
    qDebug()<<mainpageUi->onlineList->item(0)<<endl;
    qDebug()<<mainpageUi->onlineList->item(mainpageUi->onlineList->row(onlineUsr_map[playinfo->getUid()]))<<endl;
}

void Mainpage::showPlayerInfoDetail(QListWidgetItem *item){
    //弹出新窗口显示用户详细信息
    qobject_cast<PlayerInfo*>(mainpageUi->onlineList->itemWidget(item))->showDetail();
}

void Mainpage::dataRecv() {
    while(usrSocket->hasPendingDatagrams())
    {
        readPendingDatagram(usrSocket->receiveDatagram());
    }
}

void Mainpage::readPendingDatagram(QNetworkDatagram datagramRecv) {
    QByteArray data = datagramRecv.data();
    QJsonDocument dataJson = QJsonDocument::fromJson(data);
    //qDebug()<<"receive data:"<<dataJson<<endl;
    if(dataJson["DataType"] == datatype::loginyes) {
        setClientUsr(QJsonDocument::fromJson(datagramRecv.data()));
                                                //用户登陆成功,设置客户端用户信息
    }
    else if(dataJson["DataType"] == datatype::onlineusradd) {
        setOtherUsrInfo(dataJson);  //有用户登录,添加到在线用户列表
    }
    else if(dataJson["DataType"] == datatype::close) {
        eraseUsr(dataJson["uid"].toInt());  //由用户下线,删除此uid的用户
    }
}

void Mainpage::closeEvent(QCloseEvent *event) {
    //窗口关闭时, 通知服务器用户已经下线
    QJsonObject object;
    object.insert("DataType", datatype::close);
    object.insert("uid", usrUid);
    usrSocket->writeDatagram(QJsonDocument(object).toJson(), serverAddr, port);
    event->accept();
}

void Mainpage::eraseUsr(int uid) {
    //定位uid用户信息的在列表中的位置,并删除
    mainpageUi->onlineList->takeItem(mainpageUi->onlineList->row(onlineUsr_map[uid]));
    onlineUsr_map.erase(onlineUsr_map.find(uid));
    mainpageUi->onlineList->update();
}

void Mainpage::setClientUsr(QJsonDocument dataJson) {
    QJsonDocument usrinfo(dataJson["usrinfo"].toObject());
    //qDebug()<<"usr succeed:"<<usrinfo<<endl;
    QList<QVariant> pokemoninfo = dataJson["pokemoninfo"].toArray().toVariantList();

    this->usrUid = usrinfo["uid"].toInt();
    thisUsr = new Usr(usrinfo);

    //添加所有精灵
    for(int i = 0; i < pokemoninfo.length(); i++) {
        thisUsr->addPokemon(QJsonDocument(pokemoninfo[i].toJsonObject()));
    }
}
