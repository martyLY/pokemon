#ifndef USR_H
#define USR_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "pokemonmodule_global.h"
#include "global.h"

class POKEMONMODULESHARED_EXPORT Usr
{
public:
    Usr() {}
    Usr(int _uid, QString _nickName);
    Usr(QJsonDocument);
public:

    void fightFinishWin();
    void fightFinishLose();
    void addPokemon(QString pname = "default" + QString::number(Usr::defaultname));
    void addPokemon(QJsonDocument);
    void losePokemon(const QString pname);
    void setUsrAddr(QHostAddress, quint16 );
    QHostAddress getUsrHostAddr();
    quint16 getUsrHostPort();
    QByteArray toJsonUsrInfo();
    QList<QVariant> getALLPokemon();
    int getUid();
    QString getNickName() {return nickName;}
private:
    static int defaultname;
    int uid;
    QString nickName;

    uint pokemonCount;
    uint winCount;
    uint loseCount;
    uint fightCount;
    uint badgeCount;
    QVector<Pokemon*> pokemonVector;

    QHostAddress clientAddr;
    quint16 clientPort;

    void addBadgeCount();
};

#endif // USR_H
