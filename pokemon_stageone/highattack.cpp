#include "highattack.h"

void HighAttack::initPokemon() {
    this->exp = 100;
    this->cur_exp = 0;
    this->level = 1;
    this->kind = highAttack;
    //this->setRace(); //确定种类
    this->setRarity(); //确定稀有度
    this->setBaseSkill();

    QString tempRarity = RARITY[this->rarity];
    setBaseAttribute((unsigned int)(BASEATTACK*(1+coForMain[tempRarity])),
                     (unsigned int)(DEFENSEPOWER*(1+coForNormal[tempRarity])),
                     (unsigned int)(MAXHP*(1+coForNormal[tempRarity])),
                     double(WSP*(1+coForNormal[tempRarity])),
                     double(AVOID*(1+coForNormal[tempRarity])),
                     double(CRITICAL*(1+coForNormal[tempRarity])));

}

QString HighAttack::getKind() {
    return POKEMONKIND[kind];
}


void HighAttack::levelUp() {
    if(level >= MAX_LEVEL) return;
    this->level += 1;
    QString tempRarity = RARITY[this->rarity];
    setBaseAttribute((unsigned int)(base_attack*(1+coForMain[tempRarity])*(1+coLevelupMain)),
                     (unsigned int)(defense_power*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     (unsigned int)(max_hp*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (wsp*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (avoid*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (critical*(1+coForNormal[tempRarity])*(1+coLevelupNormal)));
}


//QPair<unsigned int, BaseSkill> HighAttack::Attack(){
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    unsigned int isCritical = qrand()%100;
//    if((unsigned int)critical*100 > isCritical) {
//        /*产生暴击*/
//        if(baseSkill == bloodsucking) {
//            /*吸血技能发动*/
//            battle_hp = (battle_hp+base_attack*1.5*0.05)>max_hp?(battle_hp+base_attack*1.5*0.05):max_hp;
//        }
//        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack*1.5,
//                                              baseSkill);
//    }
//    else {
//        /*未产生暴击*/
//        if(baseSkill == bloodsucking) {
//            /*吸血技能发动*/
//            battle_hp = (battle_hp+base_attack*0.05)>max_hp?(battle_hp+base_attack*0.05):max_hp;
//        }
//        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack,
//                                              baseSkill);
//    }
//}


//void HighAttack::getHurt(QPair<unsigned int, BaseSkill> damage) {
//    unsigned int hurtNumber = damage.first - defense_power;
//    /*是否回避*/
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    double isGet = qrand()%100;
//    if(isGet > avoid) {
//        /*没有回避成功,受到伤害*/
//        this->battle_hp = (battle_hp-hurtNumber>0)?battle_hp-hurtNumber:0;
//        if(damage.second == frozen) {
//            /*攻击速度减少*/
//            this->battle_wsp *= 0.1;
//        }
//        else if(damage.second == buring) {
//            /*灼烧技能*/
//            this->battle_hp -= this->max_hp*0.01;
//        }
//    }
//    else {
//        /*伤害未命中*/
//        //todo
//    }

//    if(this->battle_hp <=0) {
//        /*精灵死亡, 战斗失败*/
//        //todo
//    }
//}
