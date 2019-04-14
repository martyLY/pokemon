#ifndef ANNE_H
#define ANNE_H
#include "highspeed.h"

//高敏捷型的派生类, 精灵属性为the_dark_child_Anne
//具有pokemon基类的纯虚函数attack的实现
//并且有终极技能攻击ultimateAttack函数实现
//允许给精灵命名
class Anne : public HighSpeed
{
public:
    Anne(QString _name){ name = _name;
                            race = Race::the_dark_child_Anne;
                            baseSkill = BaseSkill::buring;
                            initPokemon();}
    //获得精灵的种族, 本精灵为the_dark_child_Anne
    //返回为种族名的字符串
    QString getRace() override;

    //pokemon基类虚函数的实现, 获得精灵的所有信息
    QString getAllAttritubeInfo() override;

    //pokemon基类纯虚函数的实现, 精灵进行终极技能攻击
    QPair<unsigned int, BaseSkill> ultimateAttack() override;

    //pokemon基类纯虚函数的实现, 精灵进行攻击
    QPair<unsigned int, BaseSkill> attack() override;

protected:
    //本精灵种族
    Race race;
};

#endif // ANNE_H
