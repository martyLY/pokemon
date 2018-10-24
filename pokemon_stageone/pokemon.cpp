#include "pokemon.h"

void Pokemon::initPokemon() {
    this->setBaseSkill();
    this->setRarity();
    this->setBaseAttribute(100, 100, 100, 0, 0, 0);
}

QString Pokemon::getAllAttritubeInfo() {
    QString info, number;
    info = "Name: " + this->name;
    info = info + '\t' + "Level: " + number.setNum(this->level) + "\n";
    //info = info + "PokemonRace: " + getRace() + "\n";
    //info = info + "Kind: " + POKEMONKIND[(int(this->kind))] + "\n";
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
        //循环以多次升级
        this->levelUp();
        cur_exp -= exp;
        exp = (unsigned int)(exp*1.2); //升级的经验值增长
    }
    this->battle_hp = max_hp; //升级生命值恢复
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

QPair<unsigned int, BaseSkill> Pokemon::baseAttack() {

    //UltimateSkill todo
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    unsigned int isCritical = qrand()%100;
    if((unsigned int)critical*100 > isCritical) {
        /*产生暴击*/
        if(baseSkill == bloodsucking) {
            /*吸血技能发动*/
            battle_hp = (battle_hp+base_attack*1.5*0.05)>max_hp?(battle_hp+base_attack*1.5*0.05):max_hp;
        }
        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack*1.5,
                                              baseSkill);
    }
    else {
        /*未产生暴击*/
        if(baseSkill == bloodsucking) {
            /*吸血技能发动*/
            battle_hp = (battle_hp+base_attack*0.05)>max_hp?(battle_hp+base_attack*0.05):max_hp;
        }
        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack,
                                              baseSkill);
    }
}

bool Pokemon::getHurt(QPair<unsigned int, BaseSkill> damage) {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    unsigned int isAvoid = qrand()%100;
    if(isAvoid > avoid) {
        unsigned int hurtNumber = damage.first - defense_power;
        this->battle_hp = (battle_hp-hurtNumber>0)?battle_hp-hurtNumber:0;

        if(battle_hp <= 0) {
            //精灵死亡,战斗结束
            //触发战斗结束信号
        }
        switch (damage.second) {
            case buring: battle_hp -= max_hp*BURING_DAMAGE;break;
            case frozen: battle_wsp -= (wsp-battle_wsp)<wsp*FROZEN_DAMAGE*FROZEN_TIME?
                                            FROZEN_DAMAGE*wsp:0;break;
            case bloodsucking: break;
        }
        return true;
    }
    else {
        //show miss
        return false;
    }
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
