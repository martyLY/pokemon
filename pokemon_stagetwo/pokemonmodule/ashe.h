#pragma once

#ifndef ASHE_H
#define ASHE_H

#include "highattack.h"

//高攻击型的派生类, 精灵属性为the_frozen_archer_Ashe
//具有pokemon基类的纯虚函数attack的实现
//并且有终极技能攻击ultimateAttack函数实现
//允许给精灵命名
class POKEMONMODULESHARED_EXPORT Ashe : public HighAttack
{
public:
    Ashe(QString _name){ name = _name;
                            race = Race::the_frozen_archer_Ashe;
                            baseSkill = BaseSkill::frozen;
                            initPokemon();}
    Ashe(QJsonDocument &);

    //获得精灵的种族, 本精灵为the_frozen_archer_Ashe
    //返回为种族名的字符串
    QString getRace() override;

    //获得精灵各属性信息
    QJsonObject toJsonAllAttritubeInfo() override;

    //pokemon基类纯虚函数的实现, 精灵进行终极技能攻击
    QPair<unsigned int, BaseSkill> ultimateAttack() override;

    //pokemon基类纯虚函数的实现, 精灵进行攻击
    QPair<unsigned int, BaseSkill> attack() override;
protected:
    //本精灵种族
    Race race;
};

#endif // ASHE_H
