#ifndef VLADIMIR_H
#define VLADIMIR_H

#include "highblood.h"

//高血量型的派生类, 精灵属性为the_crimson_reaper_Vladimir
//具有pokemon基类的纯虚函数attack的实现
//并且有终极技能攻击ultimateAttack函数实现
//允许给精灵命名
class Vladimir : public HighBlood
{
public:
    Vladimir(QString _name){ name = _name;
                            race = Race::the_crimson_reaper_Vladimir;
                            baseSkill = BaseSkill::buring;
                            initPokemon();}

    Vladimir(QJsonDocument  &);
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

#endif // VLADIMIR_H
