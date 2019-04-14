#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QObject>
#include <QWidget>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkDatagram>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QCloseEvent>
#include "global.h"
#include "playerinfo.h"
#include "usr.h"

namespace Ui {
    class Mainpage;
}

//主页面类,包括在线人数的显示
//之后会添加战斗界面进入的借口
//转换成主页面之后, 所有的udp数据包都会由主页面的socket接受
//并根据数据包类型执行相应的操作
class Mainpage : public QWidget
{
    Q_OBJECT
public:
   explicit  Mainpage(QUdpSocket *, QWidget *parent = nullptr);
    virtual ~Mainpage();

    //设置socket的端口,值为参数port
    void setSocketPort(quint16 port) {usrSocket->bind(port);}

    //获得用户uid
    int getUsrUid(){return usrUid;}

    //根据参数传进来的数据包的数据类型,决定执行不同的操作
    void readPendingDatagram(QNetworkDatagram );
protected:
    //窗口关闭时触发,告诉服务器该用户下线
    void closeEvent(QCloseEvent*);
private:
    int usrUid;  //当前客户端用户的uid
    Usr *thisUsr;  //当前客户端用户的实例
    QUdpSocket *usrSocket;
    Ui::Mainpage *mainpageUi;  //页面ui
    QMap<int, QListWidgetItem*> onlineUsr_map; //当前在线的用户列表

    //初始化socket
    void initSocket();

    //从用户在线列表中删除参数为uid的用户
    void eraseUsr(int);
public slots:
    //设置客户端用户的信息
    void setClientUsr(QJsonDocument);

    //设置在线用户的用户信息
    void setOtherUsrInfo(QJsonDocument);

    //有数据包来的时候执行的接受函数, 接受数据包
    void dataRecv();

    //显示选中用户的详细信息
    void showPlayerInfoDetail(QListWidgetItem*);
};

#endif // MAINPAGE_H
