#include "fightcore.h"

FightCore::FightCore(int fightType, Usr *_usr_red, Pokemon* _pokemon_red, Usr *_usr_blue, Pokemon *_pokemon_blue)
{
    usr_red = _usr_red;
    usr_blue = _usr_blue;

    pokemon_red = _pokemon_red;
    pokemon_blue = _pokemon_blue;

    winner = nullptr;
    loser = nullptr;

    type = fightType;
}

void FightCore::fightPrepare() {
//    connect(pokemon_blue, SIGNAL(pokemonDead()), this, SLOT(blockEverything()),Qt::DirectConnection );
//    connect(pokemon_red, SIGNAL(pokemonDead()), this, SLOT(blockEverything()), Qt::DirectConnection );
//    connect(pokemon_blue, SIGNAL(pokemonDead()), this, SLOT(redPokemonWin()),Qt::QueuedConnection);
//    connect(pokemon_red, SIGNAL(pokemonDead()), this, SLOT(bluePokemonWin()), Qt::QueuedConnection);

    //向双方发送地址请求消息,并且附带战斗双方的信息
    //发送时注意是否为机器人, 若为机器人则将昵称设为robot

    //数据包生成
    fightSocket = new QUdpSocket;
    QJsonObject gainAddr;
    gainAddr.insert("DataType", datatype::fightaddr);
    gainAddr.insert("fighttype", type);

    if(usr_blue != nullptr) {
        gainAddr.insert("bluenickname", usr_blue->getNickName());
    }
    else {
        gainAddr.insert("bluenickname", "robot");
    }
    gainAddr.insert("bluepokemoninfo", pokemon_blue->toJsonAllAttritubeInfo());

    if(usr_red != nullptr) {
        gainAddr.insert("rednickname", usr_red->getNickName());
    }
    else {
        gainAddr.insert("rednickname", "robot");
    }
    gainAddr.insert("redpokemoninfo", pokemon_red->toJsonAllAttritubeInfo());

    //发送
    if(usr_red != nullptr)
    {
        fightSocket->writeDatagram(QJsonDocument(gainAddr).toJson(),
                                   usr_red->getUsrHostAddr(), usr_red->getUsrHostPort());

        if(!fightSocket->waitForReadyRead(1*60*1000)) {
            qDebug()<<"usr timeout";
            // to do
            //等待返回信息, 如果超时未返回则应中断战斗
         }
        else {
            //记录对方的战斗程序地址和端口
            QNetworkDatagram n = fightSocket->receiveDatagram();
            redHostAddr = n.senderAddress();
            redHostPort = static_cast<quint16>(n.senderPort());
            usr_red->setFightAddr(redHostAddr, redHostPort);
        }
    }  //红色方处理, 为机器人则跳过

    if(usr_blue != nullptr)
    {

        fightSocket->writeDatagram(QJsonDocument(gainAddr).toJson(),
                                        usr_blue->getUsrHostAddr(), usr_blue->getUsrHostPort());
        if(!fightSocket->waitForReadyRead(1*60*1000)) {
            qDebug()<<"usr timeout";
            // to do
            //等待返回信息, 如果超时未返回则应中断战斗
        }
        else {
            //记录对方的战斗程序地址和端口
            QNetworkDatagram n = fightSocket->receiveDatagram();
            blueHostAddr = n.senderAddress();
            blueHostPort = static_cast<quint16>(n.senderPort());

            usr_blue->setFightAddr(blueHostAddr, blueHostPort);
        }
    }  //蓝色方处理, 为机器人则会跳过

    fightStart();  //战斗开始
}

void FightCore::fightStart() {
    isFightEnd = false;

    pokemon_red_AttackTimer = new QTimer();
    pokemon_red_AttackTimer->setSingleShot(false);  //到时重新循环
    pokemon_red_AttackTimer->setInterval(static_cast<int>(1000/(pokemon_red->getWsp()*1000))*1000);
                                                                //设置攻击间隔
    connect(pokemon_red_AttackTimer, SIGNAL(timeout()),
            this, SLOT(usr_red_AttackEvent()),Qt::DirectConnection);  //参数设为直连保证及时响应

    pokemon_blue_AttackTimer = new QTimer();
    pokemon_blue_AttackTimer->setSingleShot(false);  //到时重新循环
    pokemon_blue_AttackTimer->setInterval(static_cast<int>(1000/(pokemon_blue->getWsp()*1000))*1000);
                                                                //设置攻击间隔
    connect(pokemon_blue_AttackTimer, SIGNAL(timeout()),
            this, SLOT(usr_blue_AttackEvent()), Qt::DirectConnection);  //参数设为直连保证及时响应

    pokemon_red->setBattleMode();
    pokemon_blue->setBattleMode(); //进入战斗模式, 为战斗时的属性初始化

    pokemon_red_AttackTimer->start();
    pokemon_blue_AttackTimer->start(); // 战斗正式开始
}

void FightCore::usr_red_AttackEvent() {
    if(isFightEnd) return;  //战斗结束则返回, 不处理任何攻击信息
    DamageInfo damageinfo = pokemon_blue->getHurt(pokemon_red->Attack());  //攻击过程

    //精灵死亡时调用封锁函数
    if(pokemon_blue->getBattleHp() == 0) {
        blockEverything();
    }

    //攻击数据与客户端交互
    QUdpSocket socket;
    if(usr_red != nullptr)
    {
        QJsonObject redObject;
        redObject.insert("DataType", datatype::redattack);
        redObject.insert("damageinfo",QJsonValue(damageinfo.getDamageInfo()));
        socket.writeDatagram(QJsonDocument(redObject).toJson(),
                                redHostAddr, redHostPort);
    }

    if(usr_blue != nullptr) {
        QJsonObject blueObject;
        blueObject.insert("DataType", datatype::redattack);
        blueObject.insert("damageinfo", QJsonValue(damageinfo.getDamageInfo()));
        socket.writeDatagram(QJsonDocument(blueObject).toJson(),
                                blueHostAddr, blueHostPort);
    }

    if(pokemon_blue->getBattleHp() == 0 /*判断是否死亡*/) {
        redPokemonWin();  //后续处理
    }
}

void FightCore::usr_blue_AttackEvent() {
    if(isFightEnd) return;  //战斗结束则返回, 不处理任何攻击信息
    DamageInfo damageinfo = pokemon_red->getHurt(pokemon_blue->Attack());   //攻击过程

    //精灵死亡时调用封锁函数
    if(pokemon_red->getBattleHp() == 0) {
        blockEverything();
    }

    //攻击数据与客户端交互
    QUdpSocket socket;
    if(usr_red != nullptr)
    {
        QJsonObject redObject;
        redObject.insert("DataType", datatype::blueattack);
        redObject.insert("damageinfo",QJsonValue(damageinfo.getDamageInfo()));
        //redObject.insert("battle_up", QJsonValue::fromVariant(QVariant(pokemon_red->getBattleHp())));
        socket.writeDatagram(QJsonDocument(redObject).toJson(),
                                redHostAddr, redHostPort);
    }

    if(usr_blue != nullptr) {
        QJsonObject blueObject;
        blueObject.insert("DataType", datatype::blueattack);
        blueObject.insert("damageinfo", QJsonValue(damageinfo.getDamageInfo()));
        socket.writeDatagram(QJsonDocument(blueObject).toJson(),
                                blueHostAddr, blueHostPort);
    }

    if(pokemon_red->getBattleHp() == 0  /*判断是否死亡*/) {
        bluePokemonWin();  //后续处理
    }
}

void FightCore::redPokemonWin() {
    //断开信号
    disconnect(pokemon_blue, SIGNAL(pokemonDead()), this, SLOT(redPokemonWin()));
    disconnect(pokemon_red, SIGNAL(pokemonDead()), this, SLOT(bluePokemonWin()));

    //获得经验
    pokemon_red->expUp(pokemon_blue->getLevel()*2);

    winner = usr_red;
    loser = usr_blue;
    /*结果通知*/
    fightResultSend(usr_red, usr_blue);
    /*赛后处理*/
    switch (type) {
    case NORMALFIGHT: normalFightResultProcess(usr_red, pokemon_red,
                                                    usr_blue, pokemon_blue);  //普通战斗处理
        break;
    case DEADFIGHT: deadFightResultProcess(usr_red, pokemon_red,
                                                usr_blue, pokemon_blue);  //死斗战斗处理
        break;
    default: break;
    }
    //to do
    emit fightEnd();  //战斗过程全部结束
    //this->thread()->exit();
}

void FightCore::bluePokemonWin() {
    //断开信号
    disconnect(pokemon_blue, SIGNAL(pokemonDead()), this, SLOT(redPokemonWin()));
    disconnect(pokemon_red, SIGNAL(pokemonDead()), this, SLOT(bluePokemonWin()));
    qDebug()<<"bluewin";

    //to do

    //获得经验
    pokemon_blue->expUp(pokemon_red->getLevel()*2);

    winner = usr_blue;
    loser = usr_red;
    //this->thread()->exit();

    /*结果通知*/
    fightResultSend(usr_blue, usr_red);
    /*赛后处理*/
    switch (type) {
    case NORMALFIGHT: normalFightResultProcess(usr_blue, pokemon_blue,
                                                    usr_red, pokemon_red);   //普通战斗处理
        break;
    case DEADFIGHT: deadFightResultProcess(usr_blue, pokemon_blue,
                                                usr_red, pokemon_red);  //死斗战斗处理
        break;
    default: break;
    }

    emit fightEnd();
}

void FightCore::blockEverything() {
    isFightEnd = true;
    pokemon_blue->blockSignals(true);
    pokemon_red->blockSignals(true);
    //断开信号与槽
    disconnect(pokemon_red_AttackTimer, SIGNAL(timeout()),
            this, SLOT(usr_red_AttackEvent()));
    disconnect(pokemon_blue_AttackTimer, SIGNAL(timeout()),
            this, SLOT(usr_blue_AttackEvent()));
    //计数停止
    pokemon_blue_AttackTimer->stop();
    pokemon_red_AttackTimer->stop();
    qDebug()<<"block finish!!!";
}

void FightCore::fightResultSend(Usr *winner, Usr* loser) {
    //向胜者发送胜利通知
    if(winner != nullptr) {
        winner->fightFinishWin();

        QJsonObject result;
        result.insert("DataType", datatype::win);
        fightSocket->writeDatagram(QJsonDocument(result).toJson(),
                                   winner->getFightHostAddr(), winner->getFightHostPort());
    }

    //向败者发送失败通知
    if(loser != nullptr) {
        loser->fightFinishLose();

        QJsonObject result;
        result.insert("DataType", datatype::lose);
        fightSocket->writeDatagram(QJsonDocument(result).toJson(),
                                   loser->getFightHostAddr(), loser->getFightHostPort());
    }
}

void FightCore::normalFightResultProcess(Usr* winner, Pokemon* winnerP, Usr* loser, Pokemon* loserP) {
    /*
     * 正常决斗赛只有用户战绩的更新,和精灵等级的更新
     */
    if(winner != nullptr) {
        updateUsrInfoToDBEvent(winner);
        updatePokemonInfoToDBEvent(winner, winnerP);
    }

    if(loser != nullptr) {
        updateUsrInfoToDBEvent(loser);
        updatePokemonInfoToDBEvent(loser, loserP);
    }
}

void FightCore::deadFightResultProcess(Usr* winner, Pokemon* winnerP, Usr* loser, Pokemon* loserP) {
    /*
     *  死斗赛输者选择一个精灵给胜者
     */
    qDebug()<<"lose start";
    Pokemon *pToSend = nullptr;
    if(loser == nullptr) {
        /*败者是电脑*/
        pToSend = loserP;
    }
    else if(loser != nullptr) {
        /*败者是用户,选择一个精灵送出*/
        if(!fightSocket->waitForReadyRead(1*60*1000)) {
            /*败者选择超时*/
            pToSend = loserP;
        }
        else {
            QJsonDocument dataJson = QJsonDocument::fromJson(fightSocket->receiveDatagram().data());
            if(dataJson["DataType"] != datatype::losepokemon) {
                pToSend = loserP;
            }
            else {
                qDebug()<<"losepokemon";
                QString pNickName = dataJson["pokemonname"].toString();
                pToSend = loser->losePokemon(pNickName);
                if(loser->hasNoPokemon()){
                    /*送出后没有精灵, 随机一个精灵添加*/
                    Pokemon *pNew = loser->addPokemon();
                    addPokemonEvent(loser, pNew);
                }
            }
        }
        /*败者数据同步数据库*/
        updateUsrInfoToDBEvent(loser);
        losePokemonEvent(loser, pToSend);

    }

    if(winner != nullptr) {
        /*生成不重复的随机名字*/
        QString pname = QString::number(QRandomGenerator::global()->bounded(65535));
        while(winner->getPokemon(pname) != nullptr) {
            pname = QString::number(QRandomGenerator::global()->bounded(65535));
        }
        pToSend->setPokemonName(pname);  //重新设置名字
        winner->addPokemon(pToSend);  //添加到拥有精灵列表

        /*胜者数据同步数据库*/
        updateUsrInfoToDBEvent(winner);
        addPokemonEvent(winner, pToSend);

        /*通知胜者获得精灵*/
        QJsonObject win;
        win.insert("DataType", datatype::winpokemon);
        win.insert("pokemoninfo", pToSend->toJsonAllAttritubeInfo());

        fightSocket->writeDatagram(QJsonDocument(win).toJson(),
                                        winner->getUsrHostAddr(), winner->getUsrHostPort());
    }
}

void FightCore::addPokemonEvent(Usr* u, Pokemon* p) {
    QSqlQuery add(UdpServer::dbForEnter);
    add.prepare("insert into pokemoninfo"
                "(uid, pokemonname, pokemoninfo)"
                "values"
                "(:uid, :pokemonname, :pokemoninfo)");
    add.bindValue(":uid", u->getUid());
    add.bindValue(":pokemonname", p->getPokemonName());
    add.bindValue(":pokemoninfo", QJsonDocument(p->toJsonAllAttritubeInfo()).toJson());

    add.exec();
}

void FightCore::losePokemonEvent(Usr* u, Pokemon* p) {
    QSqlQuery lose(UdpServer::dbForEnter );
    lose.prepare("delete from pokemoninfo "
                 "where uid = :uid and pokemonname = :pokemonname");
    lose.bindValue(":uid", u->getUid());
    lose.bindValue(":pokemonname", p->getPokemonName());
}

void FightCore::updateUsrInfoToDBEvent(Usr* u) {
    QSqlQuery updateUsr(UdpServer::dbForEnter );
    updateUsr.prepare("update usrinfo "
                      "set usrinfo = :usrinfo "
                      "where uid = :uid");
    updateUsr.bindValue(":uid", u->getUid());
    updateUsr.bindValue(":usrinfo", QJsonDocument(u->toJsonUsrInfo().toObject()).toJson());

    updateUsr.exec();
}

void FightCore::updatePokemonInfoToDBEvent(Usr* u, Pokemon* p) {
    QSqlQuery update(UdpServer::dbForEnter);
    update.prepare("update pokemoninfo "
                     "set pokemoninfo = :pokemoninfo "
                     "where uid = :uid and pokemonname = :pokemonname");
    update.bindValue(":uid", u->getUid());
    update.bindValue(":pokemonname", p->getPokemonName());
    update.bindValue(":pokemoninfo", QJsonDocument(p->toJsonAllAttritubeInfo()).toJson());

    update.exec();
}
