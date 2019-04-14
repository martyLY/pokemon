#ifndef FIGHTPAGE_H
#define FIGHTPAGE_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QMessageBox>
#include <QThread>
#include "usr.h"
#include "global.h"
#include "pokemon.h"
#include "pokemonsetting.h"
#include "pokemonchoose.h"

#define NORMALFIGHT 0  //正常决斗赛模式
#define DEADFIGHT 1  //死斗决斗赛模式,需要送出精灵

namespace Ui {
class Fightpage;
}

//战斗界面, 具有与主界面不同的socket用于和服务端的战斗核心进行数据传输
//展示整个战斗过程, 目前动态信息只包含血量的变化
//静态信息包括双方master的名字, 以及战斗的宠物属性信息
class Fightpage : public QWidget
{
    Q_OBJECT
public:
    //构造函数, 参数为当前用户
    explicit Fightpage(Usr*, QWidget *parent = nullptr);
    ~Fightpage();

    //根据数据包内容做战斗开始前的准备, 包括发送空包以表示自己的socket地址和端口
    void prepare(QNetworkDatagram);

signals:
    //战斗结束时发送
    void fightend();

    //发出后主页面将会显示
    void mainpageShow();
private slots:
    //退出战斗页面
    void on_pushButton_clicked();

    //数据接受
    void dataRecv();
private:
    Usr* usr;  //本机用户
    int fightType;  //战斗类型, 0为正常决斗赛, 1为死斗决斗赛
    QWidget *mainWindowPtr;  //主窗口指针
    QUdpSocket *fightSocket;  //socket
    QHostAddress fightCoreAddr;  //服务端战斗核心地址
    quint16 fightCorePort;  //服务端战斗核心端口

    uint redHp;  //红色方hp
    uint blueHp;  //蓝色方hp
    Ui::Fightpage *ui;

    //消息处理函数
    void readPendingDatagram(QJsonDocument);

    //死斗结束后败者调用函数, 发送自己选择送出的精灵
    void sendChoosedPokemon();
};

#endif // FIGHTPAGE_H
