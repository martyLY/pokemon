#include "highspeed.h"

//高敏捷型精灵的的初始属性值
//攻击速度, 回避率相较于其他类型精灵更高
//其他与其他精灵持平
static const unsigned int BASEATTACK = 100;
static const unsigned int DEFENSEPOWER = 80;
static const unsigned int MAXHP = 1000;
static const double WSP = 0.7;
static const double AVOID = 0.1;
static const double CRITICAL = 0.2;

//升级时主属性增长系数, 主属性为攻击力
static const double coLevelupMain = 0.05;

//升级时其他属性增长系数
static const double coLevelupNormal = 0.02;


//与其他类型精灵的不同点在于setBaseAttribute函数参数的不同
//分为主要属性和次要属性
void HighSpeed::initPokemon() {
    this->exp = 100;
    this->cur_exp = 0;
    this->level = 1;
    this->kind = pokemonKind::highSpeed;
    this->setRarity();  //设置稀有度

    QString tempRarity = RARITY[this->rarity];
    setBaseAttribute(static_cast<unsigned int>(BASEATTACK*(1+coForNormal[tempRarity])),
                     static_cast<unsigned int>(DEFENSEPOWER*(1+coForNormal[tempRarity])),
                     static_cast<unsigned int>(MAXHP*(1+coForNormal[tempRarity])),
                     double(WSP*(1+coForMain[tempRarity])),
                     double(AVOID*(1+coForMain[tempRarity])),
                     double(CRITICAL*(1+coForNormal[tempRarity]))); //攻速和回避率与其他属性系数不同

}

QString HighSpeed::getKind() {
    return POKEMONKIND[kind];
}

//精灵升级时, 不同类型的精灵在不同属性上加成不同,高攻击类型精灵主要增长攻击力
//并且不同稀有度也影响增长系数,在主属性上影响更大
void HighSpeed::levelUp() {
    if(level >= MAX_LEVEL) return; //已经达到最高等级,无法继续升级
    this->level += 1;
    QString tempRarity = RARITY[this->rarity]; //根据稀有度增长属性
    setBaseAttribute(static_cast<unsigned int>(base_attack*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     static_cast<unsigned int>(defense_power*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     static_cast<unsigned int>(max_hp*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (wsp*(1+coForMain[tempRarity])*(1+coLevelupMain)),
                     double (avoid*(1+coForMain[tempRarity])*(1+coLevelupMain)),
                     double (critical*(1+coForNormal[tempRarity])*(1+coLevelupNormal)));
}

