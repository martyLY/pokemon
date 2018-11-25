#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QObject>
#include <QWidget>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkDatagram>
#include "global.h"

namespace Ui {
    class Mainpage;
}

class PlayerInfo {
public:
    PlayerInfo(){}
    PlayerInfo(int _uid, QString _nickname)
        :uid(_uid), nickname(_nickname)
    {}
    int getUid() {return uid;}
    QString getNickname() {return nickname;}
private:
    int uid;
    QString nickname;
};

class Mainpage : public QWidget
{
    Q_OBJECT
public:
   explicit  Mainpage(QWidget *parent = nullptr);
    virtual ~Mainpage();
protected:
    QUdpSocket *usrSocket;
private:
    PlayerInfo *usr;
    QList<PlayerInfo> onlinePlayer;
    void initSocket();
    void readPendingDatagram(QNetworkDatagram );
    Ui::Mainpage *mainpageUi;
public slots:
    void setUsrInfo(int _uid, QString _nickname);
    void dataRecv();
};

#endif // MAINPAGE_H
