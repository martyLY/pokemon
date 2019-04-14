#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include "global.h"
namespace Ui {
    class StartMenu;
}

//开始界面类, 是程序一开时展示的页面显示
//进入主页面后此页面将不在显示
class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QUdpSocket*, QWidget*parent = nullptr);
    ~StartMenu();

    //设置socket端口号
    void setSocketPort(quint16 port) {usrSocket->bind((port));}

    //根据数据包类型做出相应处理
    void readPendingDatagram(QNetworkDatagram );
private:
    QUdpSocket *usrSocket;  //开始页面的socket
    Ui::StartMenu *startmenuUi;  //ui界面

signals:
    //通知程序进行页面切换, 用于注册结束或者返回登录页面
    void switchPage(int);

    //通知设置在线用户信息列表
    void setOnlineUsrList(QJsonDocument);

    //通知设置客户端用户信息
    void setUsr(QJsonDocument);
public slots:

    //数据包读取
    void dataRecv();
private slots:
    //与服务端交互,确定登录信息是否正确
    void on_loginButton_clicked();

    //跳转到注册页面
    void on_signupButton_clicked();
};

#endif // STARTMENU_H
