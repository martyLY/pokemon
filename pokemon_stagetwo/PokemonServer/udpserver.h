#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <QThread>
#include <QUdpSocket>
#include <QThreadPool>
#include <QNetworkDatagram>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>
#include <QHostAddress>
#include <QMutex>
#include <iostream>
#include "global.h"
#include "usr.h"

#define serverport 2333
#define databaseHost "127.0.0.1"
#define databaseName "pokemontest"
#define databaseUsrName "mashiro"
#define databasePwd "mashiro7221!"

//存储用户地址的类, 包括地址和端口
class UsrAddr {
public:
    UsrAddr(){}
    UsrAddr(QHostAddress addr, quint16 port ):
        clientAddr(addr), clientPort(port){}

    QHostAddress getAddr() {return  clientAddr;}

    quint16 getPort() {return clientPort;}
private:
    QHostAddress clientAddr;
    quint16 clientPort;
};

//服务器类, 主要功能在于将数据包分发给线程池中运行
//实现多线程,以及并行操作
//也存储当前在线用户的列表
class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    ~UdpServer() {}

    //从在线用户列表中删除uid为参数的用户
    void eraseUsr(int);

    //获得uid为参数的用户地址信息
    UsrAddr getUsrAddr(int);

    //将数据处理类设友元类, 以允许其访问数据库
    friend class ProcessData;
private:
    QUdpSocket *udpDataRecv;  //服务端的socket
    QThreadPool *threadPool;  //线程池
    QMap<int, Usr*> onlineUsrList;  //在线用户列表
    QMap<int, UsrAddr> onlineUsrAddrList;  //在线用户地址信息列表
    QMutex onlineListMutex;  //在线用户信息的互斥锁
    static QSqlDatabase dbForEnter;  //数据库

public slots:
    void dataRecv();

    //添加用户指针到在线用户列表, 使用互斥锁防止同时访问
    void addUsrOnlineList(Usr *);
};

/*************************************************/

//数据处理类, 负责处理信息,
//每次处理信息的过程是一个线程, 并且由线程池管理
//生成数据处理类之后, 应该用qthreadpool类中的start函数将其加入线程池
//以开启一个新的线程
class ProcessData : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ProcessData(QNetworkDatagram, UdpServer*);

    //根据数据包类型调用不同的处理函数
    void run() override;

signals:
    //通知服务器类添加新的用户到数据库
    void usrLoginSucceed(Usr*);

private:
    UdpServer *usrSocket;  //socket
    QNetworkDatagram datagramRecv;  //接受到的数据包
    QHostAddress clientAddr;  //客户端的地址
    quint16 clientPort;  //客户端的端口

    //注册时,为用户分配一个uid, 返回值为那个uid
    int getNextUid();

    //处理登录请求
    void processLoginRequset(const QJsonDocument &);

    //处理注册请求
    void processSignupRequest(const QJsonDocument &);

    //处理用户下线请求
    void processCloseRequst(const QJsonDocument &);

    //注册时根据uid生成新的用户实例, 返回值为用户的指针
    Usr* generateUsr(int);
};

#endif // UDPSERVER_H
