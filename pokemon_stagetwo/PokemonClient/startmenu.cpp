#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent),
    startmenuUi(new Ui::StartMenu)
{
    startmenuUi->setupUi(this);
}

StartMenu::~StartMenu() {
    delete startmenuUi;
}

void StartMenu::initSocket() {
    user = new QUdpSocket;
    serverAddr.setAddress(QHostAddress::LocalHost);
    port = 2333;
}

void StartMenu::readPendingDatagram() {
    QJsonDocument dataReceive;
    QByteArray data;
    data.resize(user->pendingDatagramSize());
    user->readDatagram(data.data(), data.size());
    dataReceive.fromJson(data);

    if(dataReceive["DataType"] == datatype::logininyes) {
        emit switchPage(Pagename::mainpage);
    }
    else if(dataReceive["DataType"] == datatype::loginno) {
        startmenuUi->errorinfo->setText("Password fails, please try again!");
    }
}

void StartMenu::on_logininButton_clicked()
{
    //to do
        //将数据传给服务器,确定账号密码是否正确
        QJsonObject loginData;
        loginData.insert("DataType", datatype::loginin);
        loginData.insert("name", startmenuUi->loginName->text());
        loginData.insert("password", startmenuUi->loginPassword->text());
        /* to do
         * 1.缺少字符串格式判断
         * 2.缺少加密
         */
        QJsonDocument loginDataToSend(loginData);
        if(user->writeDatagram(loginDataToSend.toJson(), serverAddr, port)
                < loginDataToSend.toJson().length()) {
            //消息没有传送完, 报错
            startmenuUi->errorinfo->setText("Network errer, no send,please try again!");
        }
        else {
            //传输成功
            if(user->waitForReadyRead(600)) {
                //返回true,没有超时
                readPendingDatagram();
            }
            else {
                startmenuUi->errorinfo->setText("Network errer, no send,please try again!");
            }
        }
}

void StartMenu::on_signupButton_clicked()
{
    emit switchPage(Pagename::signuppage);
}
