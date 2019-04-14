#pragma once
#ifndef USR_H
#define USR_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QRandomGenerator>
#include "global.h"
#include "pokemonmodule_global.h"

enum POKEMONMODULESHARED_EXPORT BADGETYPE{
    golden,
    sliver,
    copper,
    nothing,
};

//用户类, 主要用于服务端, 表示在线的用户, 也用与服务端表示当前用户
//包括用户信息,例如胜负场数, 精灵数等信息
//也包含拥有精灵列表以及对精灵列表的操作
//同时在服务端,也会存储客户端的主页面地址和端口,以及战斗页面的地址和端口用于通信.
//在客户端则相反, 会存储客户端战斗核心模块的地址和端口
class POKEMONMODULESHARED_EXPORT Usr
{
public:
    Usr() {}

    //用uid, 用户昵称创建一个实例, 用于注册时初始化一个新用户
    Usr(int _uid, QString _nickName);

    //根据数据库传回的信息创建用户实例
    Usr(QJsonDocument);
public:
    //战斗结束并且获胜时调用, 会修改胜场, 总局数等信息
    void fightFinishWin();

    //战斗结束并且失败时调用,会修改败场,总局数等信息
    void fightFinishLose();

    //添加一个随机的精灵
    //参数为精灵的名字, 默认为default加数字, 并且保证不会重复
    Pokemon* addPokemon(QString pname = "default" +
                       QString::number(Usr::defaultname));

    //添加精灵的重载函数, 根据数据库的精灵数据创建精灵实例并添加
    void addPokemon(QJsonDocument);

    //添加精灵实例, 用于用户之间交换精灵所有权
    void addPokemon(Pokemon*);


    //损失一个精灵,参数为这个精灵的名字
    //会从精灵列表中将此精灵删除, 并修改拥有精灵信息, 并且返回此精灵实例
    Pokemon* losePokemon(const QString pname);

    //参数为精灵名字, 获得此名字精灵的实例
    Pokemon* getPokemon(QString);

    //是否还拥有精灵
    bool hasNoPokemon();

    //返回一定数量的精灵名字列表, 不足则返回全部
    QStringList getSomePokemonName();

    //设置用户客户端的地址和端口
    void setUsrAddr(QHostAddress, quint16);

    //设置用户客户端战斗进程的地址和端口
    void setFightAddr(QHostAddress, quint16);

    //获得客户端主页面的地址
    QHostAddress getUsrHostAddr();

    //获得客户端战斗进程的地址
    QHostAddress getFightHostAddr();

    //获得客户端主页面的端口
    quint16 getUsrHostPort();

    //获得客户端战斗进程的端口
    quint16 getFightHostPort();

    //获得用户信息数据
    QJsonValue toJsonUsrInfo();

    //获得精灵实例列表
    QList<QVariant> getALLPokemon();

    //获得uid
    int getUid();

    //获得用户昵称
    QString getNickName() {return nickName;}
private:
    //默认精灵名字计数, 用于创建不同的精灵名字
    static int defaultname;

    int uid;    //用户uid
    QString nickName; //用户昵称

    uint pokemonCount;  //精灵数量
    uint winCount;  //胜场
    uint loseCount;  //败场
    uint fightCount;  //战斗场次
    uint badgeCount;  //徽章个数
    BADGETYPE pokemonNumBadge;  //精灵数量徽章
    BADGETYPE pokemon15levelBadge;  //15级精灵数量徽章

    QVector<Pokemon*> pokemonVector;  //精灵实例列表

    QHostAddress clientAddr;  //客户端主页面地址
    QHostAddress fightaddr;  //客户端端口
    quint16 clientPort;  //客户端战斗进程地址
    quint16 fightPort;  //客户端战斗进程端口

    //增加徽章数量
    void addBadgeCount();
};

#endif // USR_H
