#include "usr.h"
#include <QVector>

int Usr::defaultname = 0;
Usr::Usr(int _uid, QString _nickName) :
    uid(_uid), nickName(_nickName)
{
    pokemonCount = 0;
    winCount = 0;
    loseCount = 0;
    fightCount = 0;
    badgeCount = 0;
}

Usr::Usr(QJsonDocument usrdata) {
    uid = usrdata["uid"].toVariant().toInt();
    nickName = usrdata["nickname"].toString();
    pokemonCount = usrdata["pokemoncount"].toVariant().toUInt();
    winCount = usrdata["wincount"].toVariant().toUInt();
    loseCount = usrdata["losecount"].toVariant().toUInt();
    fightCount = usrdata["fightcount"].toVariant().toUInt();
    badgeCount = usrdata["badgecount"].toVariant().toUInt();
}

void Usr::fightFinishWin() {
    winCount ++;
    fightCount ++;
}

void Usr::fightFinishLose() {
    loseCount ++;
    fightCount ++;
}

void Usr::addPokemon(QString pname) {

    Usr::defaultname++;
    Pokemon *p;

    //生成随机数, 随机决定生成的精灵种族
    int whatisp = QRandomGenerator::global()->bounded(RACE.size());
    switch (whatisp) {
    case Race::the_frozen_archer_Ashe : p = new Ashe(pname); break;
    case Race::the_dark_child_Anne : p = new Anne(pname); break;
    case Race::the_crimson_reaper_Vladimir : p = new Vladimir(pname); break;
    default: break;
    }

    //添加精灵进列表
    pokemonVector.push_back(p);
    pokemonCount++;
}

void Usr::addPokemon(QJsonDocument pdata ) {
    //根据数据库传回信息确定生成的精灵
    Pokemon *p;
    switch (pdata["race"].toVariant().toInt()) {
    case Race::the_frozen_archer_Ashe : p = new Ashe(pdata); break;
    case Race::the_dark_child_Anne : p = new Anne(pdata); break;
    case Race::the_crimson_reaper_Vladimir : p = new Vladimir(pdata); break;
    default:break;
    }

    pokemonVector.push_back(p);
    pokemonCount++;
}

void Usr::losePokemon(const QString pname) {
    //移除精灵列表中名为pname的精灵
    QVector<Pokemon*>::iterator iter;
    for(iter = pokemonVector.begin(); iter != pokemonVector.end(); iter++) {
        Pokemon *p = *iter;
        if(p->getPokemonName() == pname ){
            pokemonVector.erase(iter);
        }
    }
}

QJsonValue Usr::toJsonUsrInfo(){
    QJsonObject object;
    object.insert("uid", QJsonValue(uid));
    object.insert("nickname", QJsonValue(nickName));
    object.insert("pokemoncount", QJsonValue::fromVariant(pokemonCount));
    object.insert("wincount", QJsonValue::fromVariant(winCount));
    object.insert("losecount", QJsonValue::fromVariant(loseCount));
    object.insert("figtcount", QJsonValue::fromVariant(fightCount));
    object.insert("badgecount", QJsonValue::fromVariant(badgeCount));

    return QJsonValue(object);
}

QList<QVariant> Usr::getALLPokemon() {
    QList<QVariant> list; //精灵信息列表
    QVector<Pokemon*>::iterator iter;
    for(iter = pokemonVector.begin(); iter != pokemonVector.end(); iter++) {
        list.append((*iter)->toJsonAllAttritubeInfo());
    }
    return list;
}

void Usr::setUsrAddr(QHostAddress addr, quint16 port){
    clientAddr = addr;
    clientPort = port;
}

QHostAddress Usr::getUsrHostAddr() {
    return clientAddr;
}

quint16 Usr::getUsrHostPort() {
    return clientPort;
}
int Usr::getUid() {
    return this->uid;
}
