#include "vladimir.h"

QString Vladimir::getAllAttritubeInfo() {
    QString info, number;
    info = "Name: " + this->name;
    info = info + '\t' + "Level: " + number.setNum(this->level) + "\n";
    info = info + "PokemonRace: " + RACE[this->race] + "\n";
    info = info + "Kind: " + POKEMONKIND[(int(this->kind))] + "\n";
    info = info + "Rarity: " + RARITY[int(this->rarity)] + "\n";
    info = info + "BaseAttack: " + number.setNum(this->base_attack) + "\n";
    info = info + "DefensePower: " + number.setNum(this->defense_power) + "\n";
    info = info + "HP: " + number.setNum(this->max_hp) + "\n";
    info = info + "AttackSpeed: " + number.setNum(this->wsp) + "\n";
    info = info + "Avoid: " + number.setNum(this->avoid) + "\n";
    info = info + "Critical: " + number.setNum(this->critical) + "\n";
    info = info + "BaseSkill: " + BASESKILL[int(this->baseSkill)] + "\n";

    return info;
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
