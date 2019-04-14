#pragma once
#ifndef FIGHTCORE_H
#define FIGHTCORE_H

#include <QObject>
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QMutex>
#include <QUdpSocket>
#include <QThread>
#include <QHostAddress>
#include <QSqlQuery>
#include "global.h"
#include "usr.h"
#include "udpserver.h"

#define NORMALFIGHT 0  //普通战斗模式
#define DEADFIGHT 1  //死斗战斗模式

//战斗核心类, 双方精灵加入战斗后移入此类中进行处理
//建议战斗核心类加入新的线程,以实现多对战斗的进行
//并且有战斗结束和战斗开始的信号与槽用于控制战斗的开始和通知战斗的结束
class FightCore : public QObject
{
    Q_OBJECT
public:
    //构造函数, 参数一次是战斗类型, 用户及用户的精灵, 用户及用户的精灵, 其中第二组用户可以为空
    FightCore(int fightType, Usr*, Pokemon*, Usr* _usr_blue = nullptr, Pokemon* _pokemon_blue = nullptr);

    //获得决斗胜者, 战斗结束前调用会返回空
    Usr* getWinner() {return winner;}

    //或者决斗败者, 战斗结束前调用会返回空
    Usr* getLoser() {return loser;}
private:
    int type;  //战斗类型, 0为普通决斗, 1为死斗决斗
    Usr *usr_red;  //红色方master
    Usr *usr_blue;  //蓝色方master
    Pokemon *pokemon_red;  //红色方参战精灵
    Pokemon *pokemon_blue;  //蓝色方参战精灵

    Usr* winner;  //胜者, 默认为空
    Usr* loser;  //败者, 默认为空

    QHostAddress redHostAddr;  //红色方战斗程序地址
    quint16 redHostPort;  //红色方战斗进程端口

    QHostAddress blueHostAddr;  //蓝色方战斗程序地址
    quint16 blueHostPort;  //蓝色方战斗进程端口
    QUdpSocket *fightSocket;  //socket

    QTimer *pokemon_red_AttackTimer;  //红色方计时器, 用于设置攻击间隔
    QTimer *pokemon_blue_AttackTimer;  //蓝色方计时器, 用于设置攻击间隔
    QMutex singleAttack;  //单次攻击锁,
    QMutex endLock;  //结束锁,表示战斗结束, 所有攻击程序无法执行
    bool isFightEnd;  //是否结束战斗标志

    //像方法发送战斗结果
    void fightResultSend(Usr* winner, Usr* loser);

    //若为死斗模式,战斗结束后会调用此函数处理后续过程
    void deadFightResultProcess(Usr* winner, Pokemon* winnerP, Usr* loser, Pokemon* loserP);

    //若为普通战斗模式, 战斗结束后会调用此函数处理后续过程
    void normalFightResultProcess(Usr* winner, Pokemon* winnerP, Usr* loser, Pokemon* loserP);

    //死斗模式下, 战斗结束后用于处理用户获得精灵, 将精灵信息更新到数据库
    void addPokemonEvent(Usr*, Pokemon*);

    //死斗模式下, 战斗结束后用于处理用户失去精灵, 并将精灵从数据库中删除
    void losePokemonEvent(Usr*, Pokemon*);

    //更新用户的基本信息
    void updateUsrInfoToDBEvent(Usr*);

    //更新给定用户的给定精灵的信息到数据库
    void updatePokemonInfoToDBEvent(Usr*, Pokemon*);
signals:
    //战斗结束且后续处理完成后发送
    void fightEnd();
public slots:

    //战斗前准备, 包括获得参展双方战斗程序的地址和端口等信息
    void fightPrepare();

    //战斗开始, 设置定时器等信息
    void fightStart();

    //红色方进行攻击, 进行攻击结算, 与客户端数据交换
    void usr_red_AttackEvent();

    //蓝色方进行攻击, 进行攻击结算, 与客户端数据交换
    void usr_blue_AttackEvent();

    //红色方精灵胜利, 中断信号, 并且进行后续处理
    void redPokemonWin();

    //蓝色方精灵胜利, 终端信息号, 并进行后续处理
    void bluePokemonWin();

    //战斗结束后被立即调用的函数, 立即封锁所有攻击信号, 停止攻击计时器, 将结束战斗锁上锁
    void blockEverything();

};

#endif // FIGHTCORE_H
