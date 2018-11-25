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
#include <iostream>
#include "global.h"
#include "usr.h"

#define serverport 2333
#define databaseHost "127.0.0.1"
#define databaseName "pokemontest"
#define databaseUsrName "mashiro"
#define databasePwd "mashiro7221!"

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

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    ~UdpServer() {}
    friend class ProcessData;
protected:
    QUdpSocket *udpDataRecv;
    QThreadPool *threadPool;
    QMap<int, Usr*> onlineUsrList;
    QMap<int, UsrAddr> onlineUsrAddrList;
    static QSqlDatabase dbForEnter;

public slots:
    void dataRecv();
    void addUsrOnlineList(Usr*);
};

/*************************************************/

class ProcessData : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ProcessData(QNetworkDatagram, UdpServer*);
    void run() override;

signals:
    void usrLoginSucceed(Usr*);

private:
    UdpServer *usr;
    QNetworkDatagram datagramRecv;
    QHostAddress clientAddr;
    quint16 clientPort;

    int getNextUid();
    void processLoginRequset(const QJsonDocument &);
    void processSignupRequest(const QJsonDocument &);
    void processCloseRequst(const QJsonDocument &);
    Usr* generateUsr(int);
};

#endif // UDPSERVER_H
