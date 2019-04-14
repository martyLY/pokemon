#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QUdpSocket *socket, QWidget *parent) :
    mainWindowPtr(parent), usrSocket(socket), mainpageUi(new Ui::Mainpage)
{
    mainpageUi->setupUi(this);
    //在线用户列表设置成适应文本宽度模式
    mainpageUi->onlineList->setResizeMode(QListWidget::Adjust);

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

    //通知在线定时器
    isOnline = new QTimer();
    isOnline->setSingleShot(false);
    isOnline->setInterval(8*1000);
    connect(isOnline, SIGNAL(timeout), this, SLOT(sendIsOnline()));
    isOnline->start();
//    qDebug()<<mainpageUi->onlineList->count()<<endl;
//    qDebug()<<mainpageUi->onlineList<<endl;
//    qDebug()<<onlineUsr_map<<endl;
//    qDebug()<<"item:"<<item<<endl;
//    qDebug()<<"play:"<<playinfo<<endl;
//    qDebug()<<mainpageUi->onlineList->item(0)<<endl;
//    qDebug()<<mainpageUi->onlineList->item(mainpageUi->onlineList->row(onlineUsr_map[playinfo->getUid()]))<<endl;
}

void Mainpage::showPlayerInfoDetail(QListWidgetItem *item){
    //弹出新窗口显示用户详细信息
    qobject_cast<PlayerInfo*>(mainpageUi->onlineList->itemWidget(item))->showDetail();
}

void Mainpage::dataRecv() {
    qDebug()<<"mainpage has data";
    while(usrSocket->hasPendingDatagrams())
    {
        qDebug()<<"mainpage has data";
        readPendingDatagram(usrSocket->receiveDatagram());
    }
}

void Mainpage::readPendingDatagram(QNetworkDatagram datagramRecv) {
    QByteArray data = datagramRecv.data();
    QJsonDocument dataJson = QJsonDocument::fromJson(data);
    qDebug()<<"receive data:"<<dataJson<<endl;
    if(dataJson["DataType"] == datatype::loginyes) {
        setClientUsr(QJsonDocument::fromJson(datagramRecv.data()));
                                                    //用户登陆成功,设置客户端用户信息
    }
    else if(dataJson["DataType"] == datatype::onlineusradd) {
        setOtherUsrInfo(dataJson);              //有用户登录,添加到在线用户列表
    }
    else if(dataJson["DataType"] == datatype::close) {
        eraseUsr(dataJson["uid"].toInt());    //由用户下线,删除此uid的用户
    }
    else if(dataJson["DataType"] == datatype::fightaddr) {
                                                  //战斗匹配成功, 生成战斗进程,并且隐藏主页面
        Fightpage *fightcore = new Fightpage(thisUsr, mainWindowPtr);
        fightcore->prepare(datagramRecv);
        connect(fightcore, SIGNAL(fightend()), this, SLOT(show()));
        fightcore->show();
        mainWindowPtr->hide();;
    }
    else if(dataJson["DataType"] == datatype::winpokemon) {
        //弹出结果窗口
        QMessageBox *resultinfo = new QMessageBox();
        resultinfo->setWindowFlags(Qt::CustomizeWindowHint|Qt::SubWindow);
        resultinfo->setText("You Win a Pokemon");
        resultinfo->setStandardButtons(QMessageBox::Ok);
        int result = resultinfo->exec();
        if(result == QMessageBox::Ok) {
            resultinfo->close();
        }
    }
}

void Mainpage::closeEvent(QCloseEvent *event) {
    //窗口关闭时, 通知服务器用户已经下线
    QJsonObject object;
    object.insert("DataType", datatype::close);
    object.insert("uid", usrUid);
    usrSocket->writeDatagram(QJsonDocument(object).toJson(), serverAddr, port);
}

void Mainpage::eraseUsr(int uid) {
    //定位uid用户信息的在列表中的位置,并删除
    mainpageUi->onlineList->takeItem(mainpageUi->onlineList->row(onlineUsr_map[uid]));
    onlineUsr_map.erase(onlineUsr_map.find(uid));
    mainpageUi->onlineList->update();
}

void Mainpage::setClientUsr(QJsonDocument dataJson) {
    QJsonDocument usrinfo(dataJson["usrinfo"].toObject());
    this->usrUid = usrinfo["uid"].toInt();
    //qDebug()<<"usr succeed:"<<usrinfo<<endl;
    QList<QVariant> pokemoninfo = dataJson["pokemoninfo"].toArray().toVariantList();
    thisUsr = new Usr(usrinfo);
    //添加所有精灵
    for(int i = 0; i < pokemoninfo.length(); i++) {
        thisUsr->addPokemon(QJsonDocument(pokemoninfo[i].toJsonObject()));
    }
}

void Mainpage::on_matchBot_clicked()
{
    QJsonObject object;
    //数据包内容
    object.insert("DataType", datatype::matchfight);
    object.insert("uid", usrUid);
    object.insert("pokemonname", "223323");

    QUdpSocket socket;
    socket.writeDatagram(QJsonDocument(object).toJson(),
                         serverAddr, port);
}

void Mainpage::on_normalFightMatch_clicked()
{
    //调用精灵选择界面选择精灵
    pokemonChoose *choose =  new pokemonChoose(QJsonValue(QJsonArray::fromVariantList(thisUsr->getALLPokemon())),
                                               this);
    connect(choose, SIGNAL(choosedPokemon(QString)), this, SLOT(normalFightMatch(QString)));
    choose->show();
}

void Mainpage::normalFightMatch(QString pokemonName) {
    QJsonObject fightMatch;
    //数据包内容
    fightMatch.insert("DataType", datatype::matchfight);
    fightMatch.insert("uid", thisUsr->getUid());
    fightMatch.insert("pokemonname", pokemonName);
    fightMatch.insert("fighttype", NORMALFIGHT);

    usrSocket->writeDatagram(QJsonDocument(fightMatch).toJson(),
                              serverAddr, port);
}

void Mainpage::on_deadFightMatch_clicked()
{
    //调用精灵选择界面选择精灵
    pokemonChoose *choose =  new pokemonChoose(QJsonValue(QJsonArray::fromVariantList(thisUsr->getALLPokemon())),
                                               this);
    connect(choose, SIGNAL(choosedPokemon(QString)), this, SLOT(deadFightMatch(QString)));
    choose->show();
}

void Mainpage::deadFightMatch(QString pokemonName) {
    QJsonObject fightMatch;
    //数据包内容
    fightMatch.insert("DataType", datatype::matchfight );
    fightMatch.insert("uid", thisUsr->getUid());
    fightMatch.insert("pokemonname", pokemonName);
    fightMatch.insert("fighttype", DEADFIGHT);

    usrSocket->writeDatagram(QJsonDocument(fightMatch).toJson(),
                              serverAddr, port);
}

void Mainpage::sendIsOnline() {
    QJsonObject isonline;
    isonline.insert("DataType", datatype::stillonline);
    isonline.insert("DataType", thisUsr->getUid());

    usrSocket->writeDatagram(QJsonDocument(isonline).toJson(),
                                    serverAddr, port);
}
