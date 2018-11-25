#include "udpserver.h"

QSqlDatabase UdpServer::dbForEnter = QSqlDatabase::addDatabase("QMYSQL","QueryForEnter");

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
    /*新建线程放入线程池,进行数据处理*/
    ProcessData *task = new ProcessData(udpDataRecv->receiveDatagram(), this);
    connect(task, SIGNAL(usrLoginSucceed(Usr*)), this, SLOT(addUsrOnlineList(Usr*)));
    threadPool->start(task);   
}

void UdpServer::addUsrOnlineList(Usr *usr) {
    onlineUsrList[usr->getUid()] = usr;
    onlineUsrAddrList[usr->getUid()] = UsrAddr(usr->getUsrHostAddr(), usr->getUsrHostPort());

}

/*********************数据包处理***************************/

ProcessData::ProcessData(QNetworkDatagram _datagram, UdpServer* _usr) :
     usr(_usr), datagramRecv(_datagram)
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
    case datatype::close : processCloseRequst(dataRecv); break;
    default: break;
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
    query.prepare("select uid, usr_pwd from usrdata where usr_name = :loginName;");
    query.bindValue(":loginName", QVariant(loginName));
    query.exec();

    QString correctLoginPwd;
    int uid = -1;
    while(query.next()) {
        correctLoginPwd = query.value("usr_pwd").toString();
        uid = query.value("uid").toInt();
    }

    /*发送回应*/
    QJsonObject loginResponse;
    if(correctLoginPwd == loginPwd ) {
        /*to do
         * 选择1:访问得到个人信息并返回
         * 选择2:等用户第一次查看自己信息的时候在申请
         */
        Usr *u = generateUsr((uid));
        if(uid > 0) {
            emit usrLoginSucceed(u);
        }

//        qDebug()<<datatype::loginyes;
        loginResponse.insert("DataType", datatype::loginyes);
        loginResponse.insert("uid", QJsonValue(uid));
        loginResponse.insert("nickname", QJsonValue(u->getNickName()));
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

Usr* ProcessData::generateUsr(int uid) {
    /*读取用户信息和精灵列表*/
    QJsonDocument udoc;
    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("select usrinfo from usrinfo where uid = :uid;");
    query.bindValue(":uid", QVariant(uid));
    query.exec();
    while(query.next()) {
        udoc = query.value("usrinfo").toJsonDocument();
    }
    Usr* usr = new Usr(udoc);

    query.prepare("select pokemoninfo from pokemoninfo where uid = :uid;");
    query.bindValue(":uid", uid);
    query.exec();
    while (query.next()) {
        usr->addPokemon(query.value("pokemoninfo").toJsonDocument());
    }
    usr->setUsrAddr(clientAddr, clientPort);
    return usr;
}

void ProcessData::processSignupRequest(const QJsonDocument &dataRecv) {
    /*数据库新添加用户,随机一个小精灵,并且返回相关信息
     */
    QString signupName = dataRecv["account"].toString();
    QString signupPwd = dataRecv["password"].toString();
    QString pokeName = dataRecv["pokename"].toString();
    int uid = getNextUid();


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
    }
    else if(query.exec()){
        signupResponse.insert("DataType", datatype::signupyes);
        /*创建用户信息到数据库*/
        Usr usr(uid, "default");
        QSqlQuery q(UdpServer::dbForEnter);
        q.prepare("insert into usrinfo"
                  "(uid, usrinfo)"
                  "values"
                    "(:uid, :usrinfo);");
        q.bindValue(":uid", usr.getUid());
        q.bindValue(":usrinfo", usr.toJsonUsrInfo());
        q.exec();

        usr.addPokemon(pokeName);
        usr.addPokemon();
        usr.addPokemon();

        q.prepare("insert into pokemoninfo "
                  "(uid, pokemoninfo)"
                  "values"
                   "(:uid, :pokemoninfo);");
        QList<QVariant> list = usr.getALLPokemon();
        for(int i = 0; i < list.length(); i++){
            q.bindValue(":uid", uid);
            q.bindValue(":pokemoninfo", QJsonDocument(list[i].toJsonObject()).toJson());
            q.exec();
            qDebug()<<QJsonDocument(list[i].toJsonObject()).toJson()<<endl;
            qDebug()<<q.lastError()<<endl;
        }
        /*to do 输出返回信息*/
    }
    else {
        signupResponse.insert("dataType", datatype::signupno);
    }
    qDebug()<<"error:"<<query.lastError()<<endl;
    dataSend.writeDatagram(QJsonDocument(signupResponse).toJson(),
                                clientAddr, clientPort);

}

void ProcessData::processCloseRequst(const QJsonDocument &dataRecv) {
    //usr->onlineUsrList.erase(usr->onlineUsrAddrList.find());
}

int ProcessData::getNextUid() {
    /*获得最大uid号,加1后返回*/
    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("select max(uid) from usrdata");
    query.exec();

    int maxuid = 0;
    while (query.next()) {
        maxuid = query.value(0).toInt();
    }
    return maxuid+1;
}
