#include "pokemon.h"

void Pokemon::initPokemon() {
    this->setRarity();
    this->setBaseAttribute(100, 100, 100, 0, 0, 0);
}

uint Pokemon::getLevel() {
    return this->level;
}

void Pokemon::expUp(unsigned int _exp) {
    cur_exp += _exp;
    while(cur_exp > exp) {
        //循环以多次升级
        this->levelUp();
        cur_exp -= exp;
        exp = static_cast<uint>(exp*1.2); //升级的经验值增长
    }
    this->battle_hp = max_hp; //升级生命值恢复
}

void Pokemon::setBaseSkill() {
    int _baseSkill = QRandomGenerator::global()->bounded(BASESKILL.length());
    this->baseSkill = BaseSkill(_baseSkill);
}

void Pokemon::setRarity() {
    int _rarity = QRandomGenerator::global()->bounded(RARITY.length());
    this->rarity = Rarity(_rarity);
}

void Pokemon::setBaseAttribute(unsigned int _base_attack,
                                  unsigned int _defense_power,
                                  unsigned int _max_hp,
                                  double _wsp,
                                  double _avoid,
                                  double _critical){
    this->base_attack = _base_attack;
    this->defense_power = _defense_power;
    this->max_hp = _max_hp;
    this->battle_hp = _max_hp;
    this->wsp = _wsp;
    this->battle_wsp = _wsp;
    this->avoid = _avoid;
    this->critical = _critical;
}


QString Pokemon::getPokemonName() {
    return name;
}

void Pokemon::setLevel(uint _level) {
    for(uint i = 1; i < _level; i++) {
        levelUp();
    }
}

DamageInfo Pokemon::Attack() {
    return baseAttack();
}

DamageInfo Pokemon::baseAttack() {
    DamageInfo damageinfo;
    damageinfo.setIsBaseAttack();
    uint isCritical = static_cast<uint>(QRandomGenerator::global()->bounded(100));
    if(static_cast<uint>(critical*100) > isCritical) {
        /*产生暴击*/
        damageinfo.setIsCritical(true);
        damageinfo.damage = static_cast<uint>(base_attack*2);
        return damageinfo;
    }
    else {
        /*未产生暴击*/
        damageinfo.setIsCritical(false);
        damageinfo.damage = static_cast<uint>(base_attack);
        return damageinfo;
    }
}

DamageInfo Pokemon::getHurt(DamageInfo damage) {
    DamageInfo damageinfo; //实际受到的伤害类
    uint isAvoid = static_cast<uint>(QRandomGenerator::global()->bounded(100));
    if(isAvoid > avoid) {
        if(damageinfo.damageType == DamageType::baseAttack) {
            /*普通攻击*/
            uint hurtNumber = damage.damage>defense_power?damage.damage-defense_power:0;
            hurtNumber= (battle_hp>hurtNumber)?(hurtNumber):battle_hp;
            battle_hp -= hurtNumber;
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

void Pokemon::setBattleMode() {
    battle_hp = max_hp;
    battle_wsp = wsp;
}

void Pokemon::setPokemonName(QString pname) {
    name = pname;
}

