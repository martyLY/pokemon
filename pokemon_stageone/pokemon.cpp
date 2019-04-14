#include "pokemon.h"

//@function: 初始化精灵属性
void Pokemon::initPokemon() {
    this->setBaseSkill();
    this->setRarity();
    this->setBaseAttribute(100, 100, 100, 0, 0, 0);
}

QString Pokemon::getAllAttritubeInfo() {
    QString info, number;
    info = "Name: " + this->name;
    info = info + '\t' + "Level: " + number.setNum(this->level) + "\n";
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

unsigned int Pokemon::getLevel() {
    return this->level;
}

void Pokemon::expUp(unsigned int _exp) {
    cur_exp += _exp;
    while(cur_exp > exp) {
        //循环以多次升级
        this->levelUp();
        cur_exp -= exp;
        exp = static_cast<unsigned int>(exp*1.2); //升级的经验值增长
    }
    this->battle_hp = max_hp; //升级生命值恢复
}

void Pokemon::setBaseSkill() {
    int _baseSkill = QRandomGenerator::global()->bounded(BASESKILL.length()-1);
    this->baseSkill = BaseSkill(_baseSkill);
}

void Pokemon::setRarity() {
    int _rarity = QRandomGenerator::global()->bounded(RARITY.length()-1);
    this->rarity = Rarity(_rarity);
}

QPair<unsigned int, BaseSkill> Pokemon::baseAttack() {
    unsigned int isCritical = static_cast<unsigned int>(QRandomGenerator::global()->bounded(100));
    if (static_cast<unsigned int>(critical*100) > isCritical) {
        //产生暴击, 伤害为正常的1.5倍
        return QPair<unsigned int, BaseSkill>(static_cast<unsigned int>(base_attack*1.5),
                                              BaseSkill::none);
    }
    else {
        //未产生暴击
        return QPair<unsigned int, BaseSkill>(static_cast<unsigned int>(base_attack),
                                              BaseSkill::none);
    }
}

bool Pokemon::getHurt(QPair<unsigned int, BaseSkill> damage) {
    unsigned int isAvoid = static_cast<unsigned int>(QRandomGenerator::global()->bounded(100));
    if (isAvoid > avoid) {
        //伤害命中未闪避
        unsigned int hurtNumber = damage.first > defense_power ?
                                        damage.first - defense_power : 0;  //比较以防止unsigned int数值越界
        this->battle_hp = (battle_hp > hurtNumber)?battle_hp-hurtNumber:0;  //严格使用大小比较而不要用相减判断, 可能会造成越界

        if(battle_hp <= 0) {
            //精灵死亡,战斗结束
            //触发战斗结束信号
        }
        switch (damage.second) {
        case buring: battle_hp -= max_hp*BURING_DAMAGE;break;  //以最大生命值的一定比例造成伤害
        case frozen: battle_wsp -= (wsp-battle_wsp)<wsp*FROZEN_DAMAGE*FROZEN_TIME?
                                            FROZEN_DAMAGE*wsp:0;break;  //减少攻击速度,最多减少三次
        case bloodsucking: break;
        case none: break;
        }
        return true;
    }
    else {
        //攻击miss
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
