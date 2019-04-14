#pragma once

#ifndef ANNE_H
#define ANNE_H

#include "highspeed.h"

//高敏捷型的派生类, 精灵属性为the_dark_child_Anne
//具有pokemon基类的纯虚函数attack的实现
//并且有终极技能攻击ultimateAttack函数实现
//允许给精灵命名
class POKEMONMODULESHARED_EXPORT Anne : public HighSpeed
{
public:
    Anne(QString _name){ name = _name;
                            race = Race::the_dark_child_Anne;
                            baseSkill = BaseSkill::buring;
                            initPokemon();}

    Anne(QJsonDocument &);

    //获得精灵的种族, 本精灵为the_dark_child_Anne
    //返回为种族名的字符串
    QString getRace() override;

    //获得精灵各属性信息
    QJsonObject toJsonAllAttritubeInfo() override;

    //pokemon基类纯虚函数的实现, 精灵受到参数damageinfo中的攻击
    DamageInfo getHurt(DamageInfo) override;

    //pokemon基类纯虚函数的实现, 精灵进行攻击
    DamageInfo Attack() override;
protected:
    //本精灵种族
    //Race race;

    //pokemon基类纯虚函数的实现, 精灵进行终极技能攻击
    DamageInfo ultimateSkillAttack() override;
};

#endif // ANNE_H
