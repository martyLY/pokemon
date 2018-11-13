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
#include <QTime>
#include <iostream>
#include "global.h"
#define serverport 2333
#define databaseHost "127.0.0.1"
#define databaseName "pokemontest"
#define databaseUsrName "mashiro"
#define databasePwd "mashiro7221!"

class UdpServer : QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    ~UdpServer() {}
    friend class ProcessData;
protected:
    QUdpSocket *udpDataRecv;
    QThreadPool *threadPool;
    static QSqlDatabase dbForEnter;

public slots:
    void dataRecv();
};

class ProcessData : public QRunnable, QObject
{
public:
    ProcessData(QNetworkDatagram);
    void run() override;

private:
    QNetworkDatagram datagramRecv;
    QHostAddress clientAddr;
    quint16 clientPort;

    void processLoginRequset(const QJsonDocument &);
    void processSignupRequest(const QJsonDocument &);
};

#endif // UDPSERVER_H
