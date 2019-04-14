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
    dbForEnter.open();  //连接到数据库

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
    onlineListMutex.lock();  //加锁防止同时访问

    QUdpSocket u;
    QJsonObject object;
    object.insert("DataType", datatype::onlineusradd);
    object.insert("nickname",usr->getNickName());
    object.insert("uid",usr->getUid());
    object.insert("usrinfo", usr->toJsonUsrInfo());
    object.insert("pokemoninfo",QJsonValue(QJsonArray::fromVariantList(usr->getALLPokemon())));
    QMap<int, Usr*>::iterator iter;

    /*对所有在线用户通知usr上线*/
    for(iter = onlineUsrList.begin(); iter != onlineUsrList.end(); iter++)
    {
        u.writeDatagram(QJsonDocument(object).toJson(),
                          (*iter)->getUsrHostAddr(), (*iter)->getUsrHostPort());
    }

    /*对usr通知目前在线的人*/
    for(iter = onlineUsrList.begin(); iter != onlineUsrList.end(); iter++)
    {
        QJsonObject toUsr;
        toUsr.insert("DataType", datatype::onlineusradd);
        toUsr.insert("nickname", (*iter)->getNickName());
        toUsr.insert("uid", (*iter)->getUid());
        toUsr.insert("usrinfo", (*iter)->toJsonUsrInfo());
        toUsr.insert("pokemoninfo", QJsonValue(QJsonArray::fromVariantList((*iter)->getALLPokemon())));
        u.writeDatagram(QJsonDocument(toUsr).toJson(),
                          usr->getUsrHostAddr(), usr->getUsrHostPort());
    }

    onlineUsrList[usr->getUid()] = usr;
    onlineUsrAddrList[usr->getUid()] = UsrAddr(usr->getUsrHostAddr(), usr->getUsrHostPort());  //将新用户添加到在线用户列表

    onlineListMutex.unlock();  //开锁
}

void UdpServer::eraseUsr(int uid) {
    onlineListMutex.lock();  //上锁,防止同时访问

    onlineUsrAddrList.erase(onlineUsrAddrList.find(uid));
    onlineUsrList.erase(onlineUsrList.find(uid));  //从在线用户列表 和地址列表里删除次用户

    //通知所有人此uid的用户下线
    QMap<int, Usr*>::iterator iter;
    QUdpSocket u;
    QJsonObject object;
    object.insert("DataType", datatype::close);
    object.insert("uid", uid);
    for(iter = onlineUsrList.begin(); iter != onlineUsrList.end(); iter++) {
        qDebug()<<"erase:  "<<QJsonDocument(object).toJson();
        u.writeDatagram(QJsonDocument(object).toJson(),
                          (*iter)->getUsrHostAddr(), (*iter)->getUsrHostPort());
    }

    onlineListMutex.unlock();  //开锁
}

/*********************数据包处理***************************/

ProcessData::ProcessData(QNetworkDatagram _datagram, UdpServer* _usrSocket) :
     usrSocket(_usrSocket), datagramRecv(_datagram)
{
    clientAddr = QHostAddress(datagramRecv.senderAddress());
    clientPort = static_cast<quint16>(datagramRecv.senderPort());  //存储客户端地址和端口
}

void ProcessData::run() {
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
    /*
     * 处理登录请求,与数据库信息进行比对,并返回数据类型表示是否登录成功
     * 登录成功返回账户信息,包括小精灵信息以及账户信息
     */
    //qDebug()<<"login:"<<dataRecv<<endl;
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
        //密码正确,允许登录
        Usr *u = generateUsr(uid);
        if(uid > 0) {
            emit usrLoginSucceed(u);
        }
        //生成登陆成功信息
        loginResponse.insert("DataType", datatype::loginyes);
        loginResponse.insert("uid", QJsonValue(uid));
        loginResponse.insert("nickname", QJsonValue(u->getNickName()));
        loginResponse.insert("usrinfo", u->toJsonUsrInfo());
        loginResponse.insert("pokemoninfo", QJsonValue(QJsonArray::fromVariantList(u->getALLPokemon())));
    }
    else {
        //密码错误, 生成登录失败信息
        loginResponse.insert("DataType", datatype::loginno);
    }

    QJsonDocument loginResponseToSend(loginResponse);
    QUdpSocket dataSend;
    dataSend.writeDatagram(loginResponseToSend.toJson(),
                                 clientAddr, clientPort);
}

Usr* ProcessData::generateUsr(int uid) {
    //读取用户信息和精灵列表
    QJsonDocument udoc;
    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("select usrinfo from usrinfo where uid = :uid;");
    query.bindValue(":uid", uid);
    query.exec();
    while(query.next()) {
        udoc = QJsonDocument::fromJson(query.value("usrinfo").toByteArray());
    }
    Usr* usr = new Usr(udoc); //根据数据包内容生成用户实例

    //读取用户的精灵列表
    query.prepare("select pokemoninfo from pokemoninfo where uid = :uid;");
    query.bindValue(":uid", uid);
    query.exec();
    //将每个精灵添加到用户实例中
    while (query.next()) {
        usr->addPokemon(QJsonDocument::fromJson(query.value("pokemoninfo").toByteArray()));
    }
    usr->setUsrAddr(clientAddr, clientPort);  //存储客户端地址和端口信息
    return usr;
}

void ProcessData::processSignupRequest(const QJsonDocument &dataRecv) {
    /*数据库新添加用户,随机一个小精灵,并且返回相关信息*/

    //读取注册信息
    QString signupName = dataRecv["account"].toString();
    QString signupPwd = dataRecv["password"].toString();
    QString pokeName = dataRecv["pokename"].toString();
    QString nickName = dataRecv["nickname"].toString();
    int uid = getNextUid();

    //检查是否有重复的用户名
    QSqlQuery isExistName(UdpServer::dbForEnter);
    isExistName.prepare("select * from usrdata where usr_name = :signupname;");
    isExistName.bindValue(":signupname", QVariant(signupName));
    isExistName.exec();

    //账号密码准备写入
    QSqlQuery query(UdpServer::dbForEnter);
    query.prepare("insert into usrdata"
                      "(uid, usr_name, usr_pwd)"
                      "values"
                      "(:uid, :signupname, :signuppwd);");
    query.bindValue(":uid", QVariant(uid));
    query.bindValue(":signupname", QVariant(signupName));
    query.bindValue(":signuppwd", QVariant(signupPwd));

    QJsonObject signupResponse;
    QUdpSocket dataSend;
    if(isExistName.next()) {
        signupResponse.insert("DataType", datatype::signuprepeat); //重复注册
    }
    else if(query.exec() /*没有重复,将账号密码信息写入*/){
        signupResponse.insert("DataType", datatype::signupyes);  //注册成功
        //创建用户
        Usr usr(uid, nickName);
        usr.addPokemon(pokeName);
        usr.addPokemon();
        usr.addPokemon();

        //将用户信息添加到数据库
        QSqlQuery q(UdpServer::dbForEnter);
        q.prepare("insert into usrinfo"
                  "(uid, usrinfo)"
                  "values"
                    "(:uid, :usrinfo);");
        q.bindValue(":uid", usr.getUid());
        q.bindValue(":usrinfo", QJsonDocument(usr.toJsonUsrInfo().toObject()).toJson());
        q.exec();

        //将精灵信息写入
        q.prepare("insert into pokemoninfo"
                  "(uid, pokemonname, pokemoninfo)"
                  "values"
                   "(:uid, :pokemonname, :pokemoninfo);");
        QList<QVariant> list = usr.getALLPokemon();
        //每次写入一个精灵信息, 重复写入
        for(int i = 0; i < list.length(); i++){
            q.bindValue(":uid", uid);
            q.bindValue(":pokemonname", list[i].toJsonObject().value("name"));
            q.bindValue(":pokemoninfo", QJsonDocument(list[i].toJsonObject()).toJson());
            q.exec();
        }
        /*to do 输出返回信息*/
    }
    else {
        signupResponse.insert("dataType", datatype::signupno);  //注册失败
    }

    dataSend.writeDatagram(QJsonDocument(signupResponse).toJson(),
                                clientAddr, clientPort);
}

void ProcessData::processCloseRequst(const QJsonDocument &dataRecv) {
    int usrUid = dataRecv["uid"].toInt();
    usrSocket->eraseUsr(usrUid);  //通知在在线用户中删除用户
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
