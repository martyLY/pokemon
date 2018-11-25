#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QWidget *parent) :
    QWidget(parent), mainpageUi(new Ui::Mainpage)
{
    mainpageUi->setupUi(this);
    usrSocket = new QUdpSocket();
    //usrSocket->bind(QHostAddress::LocalHost, quint16(2333));
    connect(usrSocket, SIGNAL(readyRead()), this, SLOT(dataRecv()));
}

Mainpage::~Mainpage() {
    delete mainpageUi;
}

void Mainpage::setUsrInfo(int _uid, QString _nickname) {
    qDebug()<<_uid<<",,"<<_nickname<<endl;
    usr = new PlayerInfo(_uid, _nickname);
}

void Mainpage::dataRecv() {
    readPendingDatagram(usrSocket->receiveDatagram());
}

void Mainpage::readPendingDatagram(QNetworkDatagram datagramRecv) {
    QByteArray data = datagramRecv.data();
    QJsonDocument dataJson = QJsonDocument::fromJson(data);

    if(dataJson["DataType"] == datatype::loginyes) {
        qDebug()<<"error, repeat!!\n";
    }
}
