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
    fightCount = usrdata["fight"].toVariant().toUInt();
    badgeCount = usrdata["badgeCount"].toVariant().toUInt();

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
    /*
     *为用户随机添加一个小精灵
     */
    Usr::defaultname++;
    Pokemon *p;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    switch ((int)qrand()%RACE.length()) {
//    case Race::the_frozen_archer_Ashe : p = new Ashe(pname); break;
//    default: break;
//    }
    p = new Ashe(pname);
    pokemonVector.push_back(p);
    pokemonCount++;
    /* to do
     * usr数据写回
     * 精灵名字重复
     */
}

void Usr::addPokemon(QJsonDocument pdata ) {
    Pokemon *p;
    switch (pdata["race"].toVariant().toInt()) {
    case Race::the_frozen_archer_Ashe : p = new Ashe(pdata); break;
    default:break;
    }

    pokemonVector.push_back(p);
    pokemonCount++;
}

void Usr::losePokemon(const QString pname) {
    /*
     *移除一个精灵名字为pname
     */
    QVector<Pokemon*>::iterator iter;
    for(iter = pokemonVector.begin(); iter != pokemonVector.end(); iter++) {
        Pokemon *p = *iter;
        if(p->getPokemonName() == pname ){
            pokemonVector.erase(iter);
        }
    }
    /*to do
     * usr数据回写
     */

}

QByteArray Usr::toJsonUsrInfo(){
    QJsonObject object;
    object.insert("nickName", QJsonValue(nickName));
    object.insert("pokemonCount", QJsonValue::fromVariant(pokemonCount));
    object.insert("winCount", QJsonValue::fromVariant(winCount));
    object.insert("loseCount", QJsonValue::fromVariant(loseCount));
    object.insert("figtCount", QJsonValue::fromVariant(fightCount));
    object.insert("badgeCount", QJsonValue::fromVariant(badgeCount));

    return QJsonDocument(object).toJson();
}

QList<QVariant> Usr::getALLPokemon() {
    QList<QVariant> list;
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
