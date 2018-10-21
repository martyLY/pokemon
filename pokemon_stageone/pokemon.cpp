#include "pokemon.h"

QString Pokemon::getName() {
    return this->name;
}

QString Pokemon::getAllAttritubeInfo() {
    QString info, number;
    info = "Name: " + this->name;
    info = info + '\t' + "Level: " + number.setNum(this->level) + "\n";
    info = info + "PokemonRace: " + getRace() + "\n";
    info = info + "Kind: " + POKEMONKIND[(int(this->kind))] + "\n";
    info = info + "Rarity: " + RARITY[int(this->rarity)] + "\n";
    info = info + "BaseAttack: " + number.setNum(this->base_attack) + "\n";
    info = info + "DefensePower: " + number.setNum(this->defense_power) + "\n";
    info = info + "HP: " + number.setNum(this->max_hp) + "\n";
    info = info + "AttackSpeed: " + number.setNum(this->wsp) + "\n";
    info = info + "Avoid: " + number.setNum(this->avoid) + "\n";
    info = info + "Critical: " + number.setNum(this->critical) + "\n";
    info = info + "BaseSkill: " + BASESKILL[int(this->baseSkill)] + "\n";
    //info = info + "UltimateSkill" + getUltimateSkill() + "\n";

    return info;
}

unsigned int Pokemon::getLevel() {
    return this->level;
}

void Pokemon::expUp(unsigned int _exp) {
    cur_exp += _exp;
    while(cur_exp > exp) {
        this->levelUp();
        cur_exp -= exp;
        exp = (unsigned int)(exp*1.2); //升级的经验值增长
    }
    this->battle_hp = max_hp;

}

void Pokemon::setBaseSkill() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int _baseSkill = qrand()%(BASESKILL.length());
    this->baseSkill = BaseSkill(_baseSkill);
}

void Pokemon::setRarity() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int _rarity = qrand()%(RARITY.length());
    this->rarity = Rarity(_rarity);
}
