#include "highattack.h"

HighAttack::HighAttack(QString _name)
{
    cur_exp = 0;
    this->name = _name;
    this->kind = highAttack;
    this->setRace(); //确定种类
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

void HighAttack::setRace() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int _Race = qrand()%(RACE.length());
    this->race = Race(_Race);
}

QString HighAttack::getRace() {
    return RACE[this->race];
}

void HighAttack::setBaseAttribute(unsigned int _base_attack,
                                  unsigned int _defense_power,
                                  unsigned int _max_hp,
                                  double _wsp,
                                  double _avoid,
                                  double _critical){
    this->base_attack = _base_attack;
    this->defense_power = _defense_power;
    this->max_hp = _max_hp;
    this->wsp = _wsp;
    this->avoid = _avoid;
    this->critical = _critical;

}

void HighAttack::levelUp() {
    this->level += 1;
    qDebug()<<level<<endl;
    QString tempRarity = RARITY[this->rarity];
    setBaseAttribute((unsigned int)(base_attack*(1+coForMain[tempRarity])*(1+coLevelupMain)),
                     (unsigned int)(defense_power*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     (unsigned int)(max_hp*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (wsp*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (avoid*(1+coForNormal[tempRarity])*(1+coLevelupNormal)),
                     double (critical*(1+coForNormal[tempRarity])*(1+coLevelupNormal)));

}

QPair<unsigned int, BaseSkill> HighAttack::Attack(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    unsigned int isCritical = qrand()%100;
    if((unsigned int)critical*100 > isCritical) {
        if(baseSkill == bloodsucking) {
            battle_hp = (battle_hp+base_attack*1.5*0.05)>max_hp?(battle_hp+base_attack*1.5*0.05):max_hp;
        }
        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack*1.5,
                                              baseSkill);
    }
    else {
        if(baseSkill == bloodsucking) {
            battle_hp = (battle_hp+base_attack*0.05)>max_hp?(battle_hp+base_attack*0.05):max_hp;
        }
        return QPair<unsigned int, BaseSkill>((unsigned int)base_attack,
                                              baseSkill);
    }
}

void HighAttack::getHurt(QPair<unsigned int, BaseSkill> damage) {

}
