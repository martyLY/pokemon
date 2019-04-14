#include "signuppage.h"
#include "ui_signuppage.h"

SignupPage::SignupPage(QUdpSocket *socket, QWidget *parent) :
    QWidget(parent), usrSocket(socket),
    signuppageUi(new Ui::SignupPage)
{
    signuppageUi->setupUi(this);
}

void SignupPage::dataRecv() {
    while(usrSocket->hasPendingDatagrams())
    {
        readPendingDatagram(usrSocket->receiveDatagram());
    }
}

void SignupPage::readPendingDatagram(QNetworkDatagram datagram) {
    QJsonDocument dataReceive;
    dataReceive = QJsonDocument::fromJson(datagram.data()); //提取数据包内容

    if(dataReceive["DataType"] == datatype::signupyes) {
        emit switchPage(Pagename::startmenu);  //注册成功跳转到开始界面
    }
    else if(dataReceive["DataType"] == datatype::signuprepeat) {
        signuppageUi->errorinfo->setText("用户名重复"); //用户重复错误提示
    }
    else {
        signuppageUi->errorinfo->setText("注册未成功,请重试:");  //错误信息提示
    }
}

void SignupPage::on_generatePokemon_clicked()
{
    //将注册信息传给服务器

    signuppageUi->errorinfo->clear(); //清空错误信息

    if(signuppageUi->signupPassword->text() != signuppageUi->signupPasswordConfirm->text()) {
        signuppageUi->errorinfo->setText("密码输入不一致！"); //提示两次密码输入不一致
        return;
    }

    if(signuppageUi->signupAccount->text().isEmpty() ||
            signuppageUi->signupPassword->text().isEmpty() ||
            signuppageUi->signupPasswordConfirm->text().isEmpty() ||
            signuppageUi->signupAccount->text().isEmpty() ||
            signuppageUi->signupNickName->text().isEmpty()) {
        signuppageUi->errorinfo->setText("个人信息不能为空！");  //判断是否有信息为空
        return;
    }

    /* to do
     * 缺少申请字符串的检查
     */
    QJsonObject signupData;
    signupData.insert("DataType",datatype::signup);
    signupData.insert("account",QJsonValue(signuppageUi->signupAccount->text()));
    signupData.insert("password",QJsonValue(signuppageUi->signupPassword->text()));
    signupData.insert("pokename",QJsonValue(signuppageUi->pokemonName->text()));
    signupData.insert("nickname",QJsonValue(signuppageUi->signupNickName->text()));
    QJsonDocument signupDataToSend(signupData);  //生成数据包
    
    if(usrSocket->writeDatagram(signupDataToSend.toJson(), serverAddr, port) == -1) {
        //消息没有传完, 提醒
        signuppageUi->errorinfo->setText("网络错误,请重试");
    }
    else {
        if(usrSocket->waitForReadyRead(600)) {
            //readPendingDatagram();
        }
        else {
            //没有回应,报错
            signuppageUi->errorinfo->setText("服务器无响应, 请重试");
        }
    }
}

void SignupPage::on_back_clicked()
{
    //返回主页面时会清空所有注册页面的信息
    signuppageUi->pokemonName->clear();
    signuppageUi->signupNickName->clear();
    signuppageUi->signupAccount->clear();
    signuppageUi->signupPassword->clear();
    signuppageUi->signupPasswordConfirm->clear();
    emit switchPage(0);  //跳转主页面
}
