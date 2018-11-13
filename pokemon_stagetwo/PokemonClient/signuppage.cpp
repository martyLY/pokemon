#include "signuppage.h"
#include "ui_signuppage.h"

SignupPage::SignupPage(QWidget *parent) :
    QWidget(parent),
    signuppageUi(new Ui::SignupPage)
{
    signuppageUi->setupUi(this);
    initSocket();
}

void SignupPage::initSocket() {
    user = new QUdpSocket();
}

void SignupPage::readPendingDatagram() {
    QJsonDocument dataReceive;
    QByteArray data;
    while(user->hasPendingDatagrams()){
        data.resize(user->pendingDatagramSize());
        user->readDatagram(data.data(), data.size());
        dataReceive = QJsonDocument::fromJson(data);
        if(dataReceive["DataType"] == datatype::signupyes) {
            //to do 提示注册成功
            emit switchPage(Pagename::startmenu);
        }
        else if(dataReceive["DataType"] == datatype::signuprepeat) {
            //to do 提示用户名重复
            qDebug()<<"用户名重复"<<endl;
        }
        else {
            //to do 注册未成功
            qDebug()<<"注册未成功,请重试"<<endl;
        }
    }
}



void SignupPage::on_generatePokemon_clicked()
{
    //将注册信息传给服务器
    if(signuppageUi->signupPassword->text() != signuppageUi->signupPasswordConfirm->text()) {
        /*to do
         * 提示两次密码输入不一致
         */
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
    
    QJsonDocument signupDataToSend(signupData);
    
    if(user->writeDatagram(signupDataToSend.toJson(), serverAddr, port) == -1) {
        //消息没有传完, 提醒
        qDebug()<<"消息没有传完"<<endl;
    }
    else {
        if(user->waitForReadyRead(600)) {
            readPendingDatagram();
        }
        else {
            //没有回应,报错
            qDebug()<<"没有回应,报错"<<endl;
        }
    }
}
