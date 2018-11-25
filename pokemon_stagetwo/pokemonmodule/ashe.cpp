#include "ashe.h"

//QString Ashe::getAllAttritubeInfo() {
//    QString info, number;
//    info = "Name: " + this->name;
//    info = info + '\t' + "Level: " + number.setNum(this->level) + "\n";
//    qDebug()<<this->race<<','<<this->kind<<endl;
//    info = info + "PokemonRace: " + RACE[this->race] + "\n";
//    info = info + "Kind: " + POKEMONKIND[(int(this->kind))] + "\n";
//    info = info + "Rarity: " + RARITY[int(this->rarity)] + "\n";
//    info = info + "BaseAttack: " + number.setNum(this->base_attack) + "\n";
//    info = info + "DefensePower: " + number.setNum(this->defense_power) + "\n";
//    info = info + "HP: " + number.setNum(this->max_hp) + "\n";
//    info = info + "AttackSpeed: " + number.setNum(this->wsp) + "\n";
//    info = info + "Avoid: " + number.setNum(this->avoid) + "\n";
//    info = info + "Critical: " + number.setNum(this->critical) + "\n";
//    info = info + "BaseSkill: " + BASESKILL[int(this->baseSkill)] + "\n";
//    //info = info + "UltimateSkill" + getUltimateSkill() + "\n";

//    return info;
//}

Ashe::Ashe(QJsonDocument &pdoc) {
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

QJsonObject Ashe::toJsonAllAttritubeInfo() {
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

QString Ashe::getRace() {
    return RACE[race];
}
