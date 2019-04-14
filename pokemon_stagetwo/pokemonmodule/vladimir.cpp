#include "vladimir.h"

Vladimir::Vladimir(QJsonDocument &pdoc) {
    this->name = pdoc["name"].toString();
    this->level = pdoc["level"].toVariant().toUInt();
    this->exp = pdoc["exp"].toVariant().toUInt();
    this->cur_exp = pdoc["cur_exp"].toVariant().toUInt();
    this->base_attack = pdoc["base_attack"].toVariant().toUInt();
    this->defense_power = pdoc["defense_power"].toVariant().toUInt();
    this->max_hp = pdoc["max_hp"].toVariant().toUInt();
    this->battle_hp = this->max_hp;
    this->wsp = pdoc["wsp"].toVariant().toDouble();
    this->battle_wsp = this->wsp;
    this->avoid = pdoc["avoid"].toVariant().toDouble();
    this->critical = pdoc["critical"].toVariant().toDouble();
    this->rarity = Rarity(pdoc["rarity"].toVariant().toInt());
    this->baseSkill = BaseSkill(pdoc["baseskill"].toVariant().toInt());
    this->race = Race(pdoc["race"].toVariant().toInt());
}

QJsonObject Vladimir::toJsonAllAttritubeInfo() {
    QJsonObject pdata;
    pdata.insert("race", QJsonValue::fromVariant(QVariant(race)));
    pdata.insert("name", QJsonValue::fromVariant(QVariant(name)));
    pdata.insert("level", QJsonValue::fromVariant(QVariant(level)));
    pdata.insert("exp", QJsonValue::fromVariant(QVariant(exp)));
    pdata.insert("cur_exp", QJsonValue::fromVariant(QVariant(cur_exp)));
    pdata.insert("base_attack", QJsonValue::fromVariant(QVariant(base_attack)));
    pdata.insert("defense_power", QJsonValue::fromVariant(QVariant(defense_power)));
    pdata.insert("max_hp", QJsonValue::fromVariant(QVariant(max_hp)));
    pdata.insert("wsp", QJsonValue::fromVariant(QVariant(wsp)));
    pdata.insert("avoid", QJsonValue::fromVariant(QVariant(avoid)));
    pdata.insert("critical", QJsonValue::fromVariant(QVariant(critical)));
    pdata.insert("rarity", QJsonValue::fromVariant(QVariant(rarity)));
    pdata.insert("baseskill", QJsonValue::fromVariant(QVariant(baseSkill)));

    return pdata;
}

QString Vladimir::getRace() {
    return RACE[race];
}

QPair<unsigned int, BaseSkill> Vladimir::ultimateAttack() {
    /*此精灵的攻击与防御力,攻击力,和当前血量有关*/
    uint d = static_cast<uint>(base_attack*(1.2) + defense_power*0.5 + battle_hp%70);
                                                //伤害由攻击力, 防御力, 当前血量组合而来
    return QPair<unsigned int, BaseSkill>(d, baseSkill);
}

QPair<unsigned int, BaseSkill> Vladimir::attack() {
    unsigned int isBaseAttack = static_cast<unsigned int>(QRandomGenerator::global()->bounded(100));
    if (isBaseAttack <= 70 /*有70%概率普通攻击*/) {
        //普通攻击
        return baseAttack();
    }
    else {
        //特殊技能攻击
        return ultimateAttack();
    }
}
