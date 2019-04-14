#ifndef DAMAGEINFO_H
#define DAMAGEINFO_H

#include <QJsonObject>
#include <QVariant>
#include "pokemonsetting.h"

enum DamageType {
    baseAttack = 0,
    ultimateskill,
    miss,
};

//伤害类, 此类用于存储精灵攻击时造成的普通攻击伤害或者终极技能类型
class DamageInfo
{
public:
    DamageInfo();

    DamageType damageType; //伤害类型
    uint damage;  //造成的伤害数值
    BaseSkill ultimateSkill;  //终极技能类型
    bool isCritical;  //是否暴击
    QJsonObject getDamageInfo(); //返回伤害类型的所有信息
    void setDamageInfo(QJsonObject );  //根据信息生成伤害类

    //设置此次伤害为基本攻击
    void setIsBaseAttack(){damageType = DamageType::baseAttack;}

    //设置此次伤害为终极攻击
    void setIsUltimateSkill() {damageType = DamageType::ultimateskill;}

    //设置此次伤害被闪躲
    void setIsMiss() {damageType = DamageType::miss;}

    //设置是否暴击
    void setIsCritical(bool is) {isCritical = is;}
};

#endif // DAMAGEINFO_H
