#include "udpserver.h"

QSqlDatabase UdpServer::dbForEnter = QSqlDatabase::addDatabase("QMYSQL","QueryForEnter");
int randomUid();
/*********************Udp服务器实现*************************/

UdpServer::UdpServer(QObject *parent):
    QObject(parent)
{
    std::cout<<"system begin\n";
    dbForEnter.setHostName(databaseHost);
    dbForEnter.setDatabaseName(databaseName);
    dbForEnter.setUserName(databaseUsrName);
    dbForEnter.setPassword(databasePwd);
    dbForEnter.open();

    this->udpDataRecv = new QUdpSocket(this);
    this->udpDataRecv->bind(serverport);
    this->threadPool = new QThreadPool;
    connect(udpDataRecv, SIGNAL(readyRead()), this, SLOT(dataRecv()));
}

void UdpServer::dataRecv() {
    ProcessData *task = new ProcessData(udpDataRecv->receiveDatagram());
    threadPool->start(task);   
}

/*********************数据包处理***************************/

ProcessData::ProcessData(QNetworkDatagram _datagram) :
    datagramRecv(_datagram)
{

    clientAddr = QHostAddress(datagramRecv.senderAddress());
    clientPort = (quint16)datagramRecv.senderPort();
}

void ProcessData::run() {
    //std::cout<<"in thread:"<<datagram.data().data();
    QByteArray data = datagramRecv.data();
    QJsonDocument dataRecv = QJsonDocument::fromJson(data);

    switch (dataRecv["DataType"].toInt()) {
        case datatype::login : processLoginRequset(dataRecv); break;
        case datatype::signup : processSignupRequest(dataRecv); break;

        //todo other request
    }
}

void ProcessData::processLoginRequset(const QJsonDocument &dataRecv) {
    /*处理登录请求,与数据库信息进行比对,并返回数据类型表示是否登录成功
     * 登录成功返回账户信息,包括小精灵信息以及账户信息
     */
    QString loginName = dataRecv["name"].toString();
    QString loginPwd = dataRecv["pwd"].toString();

    /*获取用户名的正确密码*/
    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("select usr_pwd from usrdata where usr_name = :loginName;");
    query.bindValue(":loginName", QVariant(loginName));
    query.exec();

    QString correctLoginPwd;
    while(query.next()) {
        correctLoginPwd = query.value("usr_pwd").toString();
    }

    /*发送回应*/
    QJsonObject loginResponse;
    if(correctLoginPwd == loginPwd ) {
        /*to do
         * 选择1:访问得到个人信息并返回
         * 选择2:等用户第一次查看自己信息的时候在申请
         */
//        qDebug()<<datatype::loginyes;
        loginResponse.insert("DataType", datatype::loginyes);
    }
    else {
//        qDebug()<<"pwd wrong";
        loginResponse.insert("DataType", datatype::loginno);
    }

    QJsonDocument loginResponseToSend(loginResponse);
    QUdpSocket dataSend;
    dataSend.writeDatagram(loginResponseToSend.toJson(),
                                 clientAddr, clientPort);

    //std::cout<<"login:\n"<<data.data();
}

void ProcessData::processSignupRequest(const QJsonDocument &dataRecv) {
    /*数据库新添加用户,随机一个小精灵,并且返回相关信息
     */
    QString signupName = dataRecv["account"].toString();
    QString signupPwd = dataRecv["password"].toString();
    QString pokeName = dataRecv["pokename"].toString();
    int uid = randomUid();
    qDebug()<<dataRecv.toJson();
    qDebug()<<signupName<<"\t"<<signupPwd<<'\t'<<pokeName<<endl;

    /*数据库写入*/

    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("insert into usrdata"
                      "(uid, usr_name, usr_pwd)"
                      "values"
                      "(:uid, :signupname, :signuppwd);");
    query.bindValue(":uid", QVariant(uid));
    query.bindValue(":signupname", QVariant(signupName));
    query.bindValue(":signuppwd", QVariant(signupPwd));

    /* 检查是否有重复的用户名*/
    QSqlQuery isExistName(UdpServer::dbForEnter);
    isExistName.prepare("select * from usrdata where usr_name = :signupname;");
    isExistName.bindValue(":signupname", QVariant(signupName));
    isExistName.exec();

    QJsonObject signupResponse;
    QUdpSocket dataSend;
    if(isExistName.next()) {
        signupResponse.insert("DataType", datatype::signuprepeat);
        qDebug()<<"repeat\n";
    }
    else if(query.exec()){
        signupResponse.insert("DataType", datatype::signupyes);
    }
    else {
        signupResponse.insert("dataType", datatype::signupno);
    }
    dataSend.writeDatagram(QJsonDocument(signupResponse).toJson(),
                                clientAddr, clientPort);
    //std::cout<<"signup\n"<<data.data();
}

int randomUid() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return (int)(qrand()%10000);
}
