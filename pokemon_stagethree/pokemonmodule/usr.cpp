#include "usr.h"

int Usr::defaultname = 0;

Usr::Usr(int _uid, QString _nickName) :
    uid(_uid), nickName(_nickName)
{
    pokemonCount = 0;
    winCount = 0;
    loseCount = 0;
    fightCount = 0;
    badgeCount = 0;
    pokemon15levelBadge = BADGETYPE::nothing;
    pokemonNumBadge = BADGETYPE::nothing;
}

Usr::Usr(QJsonDocument usrdata) {
    uid = usrdata["uid"].toVariant().toInt();
    nickName = usrdata["nickname"].toString();
    pokemonCount = usrdata["pokemoncount"].toVariant().toUInt();
    winCount = usrdata["wincount"].toVariant().toUInt();
    loseCount = usrdata["losecount"].toVariant().toUInt();
    fightCount = usrdata["fightcount"].toVariant().toUInt();
    badgeCount = usrdata["badgecount"].toVariant().toUInt();
    pokemonNumBadge = BADGETYPE(usrdata["pokemonNumBadge"].toVariant().toInt());
    pokemon15levelBadge = BADGETYPE(usrdata["pokemon15level"].toVariant().toInt());
}

QStringList Usr::getSomePokemonName() {
    QStringList list;
    if(pokemonVector.size() <= 3) {
        for(int i = 0; i < pokemonVector.size(); i++) {
            list.append(pokemonVector[i]->getPokemonName());
        }
        return list;
    }
    else {
        int index = QRandomGenerator::global()->bounded(pokemonVector.size()-1);
        for(int i = 0; i < 3; i++) {
            list.append(pokemonVector[(index+i)%pokemonVector.size()]->getPokemonName());
        }
        return list;
    }
}

void Usr::fightFinishWin() {
    winCount ++;
    fightCount ++;
}

void Usr::fightFinishLose() {
    loseCount ++;
    fightCount ++;
}

Pokemon* Usr::addPokemon(QString pname) {

    Usr::defaultname++;
    Pokemon *p = nullptr;

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

    return p;
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

void Usr::addPokemon(Pokemon *p) {
    pokemonVector.push_back(p);
    pokemonCount++;
}

Pokemon* Usr::losePokemon(const QString pname) {
    //移除一个精灵名字为pname
    Pokemon* returnPokemon = nullptr;

    //荀川查找名字为pname的精灵
    QVector<Pokemon*>::iterator iter;
    for(iter = pokemonVector.begin(); iter != pokemonVector.end(); iter++) {
        Pokemon *p = *iter;
        if(p->getPokemonName() == pname ){
            returnPokemon = *iter;
            pokemonVector.erase(iter);
            break;
        }
    }
    return returnPokemon;
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
    object.insert("pokemonNumBadge", QJsonValue::fromVariant(pokemonNumBadge));
    object.insert("pokemon15levelBadge", QJsonValue::fromVariant(pokemon15levelBadge));

    return QJsonValue(object);
}

QList<QVariant> Usr::getALLPokemon() {
    QList<QVariant> list;  //精灵信息列表
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

void Usr::setFightAddr(QHostAddress addr, quint16 port) {
    fightaddr = addr;
    fightPort = port;
}

QHostAddress Usr::getUsrHostAddr() {
    return clientAddr;
}

quint16 Usr::getUsrHostPort() {
    return clientPort;
}

QHostAddress Usr::getFightHostAddr() {
    return fightaddr;
}

quint16 Usr::getFightHostPort() {
    return fightPort;
}

int Usr::getUid() {
    return this->uid;
}

Pokemon* Usr::getPokemon(QString pname) {
    //返回精灵名字为pname的精灵, 但不从精灵列表中去除
    QVector<Pokemon*>::iterator iter;
    for(iter = pokemonVector.begin(); iter != pokemonVector.end(); iter ++) {
        if((*iter)->getPokemonName() == pname) {
            return *iter;
        }
    }
    return nullptr;
}

bool Usr::hasNoPokemon() {
    return pokemonVector.isEmpty();
}
