#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QJsonValue>
#include <QTime>
#include <QMessageBox>

#include "global.h"
namespace Ui {
    class SignupPage;
}

//注册界面类, 包含ui界面, 用于用户选择注册时的页面显示
class SignupPage : public QWidget
{
    Q_OBJECT
public:
    //构造函数, 参数为主页面socket
    explicit SignupPage(QUdpSocket*, QWidget *parent = nullptr);

    //设置socket端口号
    void setSocketPort(quint16 port) {usrSocket->bind((port));}

    //根据数据包类型做出相应处理
    void readPendingDatagram(QNetworkDatagram );
private:
    QUdpSocket *usrSocket;  //注册页面的socket

    Ui::SignupPage *signuppageUi;
signals:
    //通知程序进行页面切换, 用于注册结束或者返回登录页面
    void switchPage(int);
public slots:
    //数据包读取
    void dataRecv();
private slots:
    //向服务器发送生成新用户的请求
    void on_generatePokemon_clicked();

    //返回登录页面
    void on_back_clicked();
};

#endif // SIGNUPPAGE_H
