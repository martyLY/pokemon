#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QUdpSocket *socket, QWidget *parent) :
    QWidget(parent), usrSocket(socket),
    startmenuUi(new Ui::StartMenu)
{
    startmenuUi->setupUi(this);
    startmenuUi->loginPassword->setEchoMode(QLineEdit::Password);
}

StartMenu::~StartMenu() {
    delete startmenuUi;
}


void StartMenu::dataRecv() {
    while(usrSocket->hasPendingDatagrams())
    {
        readPendingDatagram(usrSocket->receiveDatagram());
    }

}

void StartMenu::readPendingDatagram(QNetworkDatagram datagram) {
    startmenuUi->errorinfo->clear();

    QJsonDocument dataReceive;
    dataReceive = QJsonDocument::fromJson(datagram.data());  //获取数据包信息
    if(dataReceive["DataType"] == datatype::loginyes) {
        //登陆成功
        emit setUsr(dataReceive);  //根据数据包内容设置本用户信息
        emit switchPage(Pagename::mainpage);  //跳转主页面
    }
    else if(dataReceive["DataType"] == datatype::loginno) {
        startmenuUi->errorinfo->setText("Password fails, please try again!");
                                                    //注册失败消息显示
    }
    else if(dataReceive["DataType"] == datatype::onlineusradd) {
        //用户上线通知
        emit setOnlineUsrList(dataReceive);  //根据数据包内容更新信息
    }
    else if(dataReceive["DataType"] == datatype::loginrepeat) {
        startmenuUi->errorinfo->setText("此用户已经登录!");
    }
}

void StartMenu::on_loginButton_clicked()
{
    //登录过程说明, 客户端发送账号密码信息, 并且等待服务端做出响应
    if(startmenuUi->loginPassword->text().isEmpty() || startmenuUi->loginName->text().isEmpty()) {
        //账户或者密码为空
        startmenuUi->errorinfo->setText("用户名或密码为空!");
    }
    else {
        //将数据传给服务器,确定账号密码是否正确
        QJsonObject loginData;
        loginData.insert("DataType", datatype::login);
        loginData.insert("name", QJsonValue(startmenuUi->loginName->text()));
        loginData.insert("pwd", QJsonValue(startmenuUi->loginPassword->text()));
        /* to do
         * 1.缺少字符串格式判断
         * 2.缺少加密
         */
        QJsonDocument loginDataToSend(loginData);

        if(usrSocket->writeDatagram(loginDataToSend.toJson(), serverAddr, port) == -1) {
            //消息没有传送完, 报错
            startmenuUi->errorinfo->setText("网络错误，请重试");
        }
        else {
            //传输成功
            if(usrSocket->waitForReadyRead(600)) {
                //返回true,没有超时
                //readPendingDatagram();
            }
            else {
                startmenuUi->errorinfo->setText("网络超时，请重试");
            }
        }
    }
}

void StartMenu::on_signupButton_clicked()
{
    emit switchPage(Pagename::signuppage);
}
