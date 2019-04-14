#include "damageinfo.h"

DamageInfo::DamageInfo()
{
    damageType = DamageType(0);
    damage = 0;
    ultimateSkill =  BaseSkill(0);
    isCritical = false;
}

QJsonObject DamageInfo::getDamageInfo() {
    QJsonObject object;
    object.insert("damagetype",damageType);
    object.insert("damage",QJsonValue::fromVariant(QVariant(damage)));
    object.insert("baseskill", ultimateSkill);
    object.insert("iscritical",QJsonValue::fromVariant(isCritical));

    return object;
}

void DamageInfo::setDamageInfo(QJsonObject info) {
    damageType = DamageType(info["damagetype"].toInt());
    damage = info["damage"].toVariant().toUInt();
    ultimateSkill = BaseSkill(info["baseskill"].toInt());
    isCritical = info["iscritical"].toVariant().toBool();
}
