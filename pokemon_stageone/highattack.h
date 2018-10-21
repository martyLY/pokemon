#ifndef HIGHATTACK_H
#define HIGHATTACK_H

#include <QObject>
#include "pokemon.h"

/*高攻击力的初始属性值*/
const unsigned int BASEATTACK = 200;
const unsigned int DEFENSEPOWER = 80;
const unsigned int MAXHP = 100;
const double WSP = 0.7;
const double AVOID = 0.08;
const double CRITICAL = 0.1;

/*升级属性增长系数*/
const double coLevelupMain = 0.05;
const double coLevelupNormal = 0.02;

class HighAttack : public Pokemon
{
public:
    HighAttack(QString _name);
    ~HighAttack() override {}
    QString getRace() override;
    //QString getUltimateSkill() override;

protected:

    void levelUp() override;
    QPair<unsigned int, BaseSkill> Attack() override;
    void getHurt(QPair<unsigned int, BaseSkill> damage) override;
    //void skillAttack() override;
    void setRace() override;
    //void setUltimateSkill() override;
    void setBaseAttribute(unsigned int _base_attack,
                          unsigned int _defense_power,
                          unsigned int _max_hp,
                          double _wsp,
                          double _avoid,
                          double _critical) override;

};

#endif // HIGHATTACK_H
