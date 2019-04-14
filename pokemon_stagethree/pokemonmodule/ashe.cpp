#include "ashe.h"

Ashe::Ashe(QJsonDocument &pdoc) {
    this->name = pdoc["name"].toString();
    this->level = pdoc["level"].toVariant().toUInt();
    this->exp = pdoc["exp"].toVariant().toUInt();
    this->cur_exp = pdoc["cur_exp"].toVariant().toUInt();
    this->base_attack = pdoc["base_attack"].toVariant().toUInt();
    this->defense_power = pdoc["defense_power"].toVariant().toUInt();
    this->max_hp = pdoc["max_hp"].toVariant().toUInt();
    this->battle_hp = this->max_hp;
    qDebug()<<battle_hp;
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

DamageInfo Ashe::Attack() {
    /*to do 可能是终极击,也可能是基础攻击*/
    int isBaseAttack = QRandomGenerator::global()->bounded(100);
    if(isBaseAttack<80) {
        return baseAttack();
    }
    else
    {
        return  ultimateSkillAttack();
    }
}

DamageInfo Ashe::ultimateSkillAttack() {
    /*此精灵的攻击与攻速,攻击力,和当前血量有关*/
    uint d = static_cast<uint>(base_attack*(1.2 + (wsp+1)) + battle_hp%100);
    DamageInfo damage;
    damage.damage = d;
    damage.setIsUltimateSkill();
    damage.ultimateSkill = baseSkill;
    return damage;
}

DamageInfo Ashe::getHurt(DamageInfo damage) {
    DamageInfo damageinfo;
    uint isAvoid = static_cast<uint>(QRandomGenerator::global()->bounded(100));
    if(isAvoid > avoid) {
        if(damageinfo.damageType == DamageType::baseAttack ) {
            /*普通攻击*/
            uint hurtNumber = damage.damage>defense_power?damage.damage-defense_power:0;
            hurtNumber= (battle_hp>hurtNumber)?(hurtNumber):battle_hp;
            battle_hp -= hurtNumber;
            damageinfo.damage = hurtNumber;
        }
        else if(damageinfo.damageType == DamageType::ultimateskill) {
            uint hurtNumber = 0;
            switch (damageinfo.ultimateSkill) {
            case frozen: hurtNumber = damage.damage>defense_power?damage.damage-defense_power:0;
                hurtNumber= (battle_hp>hurtNumber)?(hurtNumber):battle_hp;
                battle_hp -= hurtNumber;
                break;
            case buring: battle_wsp -= (wsp-battle_wsp)<wsp*FROZEN_DAMAGE*FROZEN_TIME?
                                           FROZEN_DAMAGE*wsp:0;break;
            case bloodsucking: break;
            }
            damageinfo.damage = hurtNumber;
        }

        if(battle_hp <= 0) {
            //精灵死亡,战斗结束
            //触发战斗结束信号
            qDebug()<<"dead"<<endl;
            emit pokemonDead();
        }
        return damageinfo;
    }
    else {
        //show miss
        damageinfo.setIsMiss();
        return damageinfo;
    }
}
