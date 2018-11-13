#ifndef POKEMON_H
#define POKEMON_H

#endif // POKEMON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QtGlobal>
#include <QMap>
#include "pokemonsetting.h"
class Pokemon : public QObject
{
    Q_OBJECT
public:
    Pokemon():name("Pokemon"),level(1),exp(100),cur_exp(0){initPokemon();}
    ~Pokemon(){}


    unsigned int getLevel();
    void expUp(unsigned int exp);
    QPair<unsigned int, BaseSkill> baseAttack();
    bool getHurt(QPair<unsigned int, BaseSkill> damage);
    //virtual QString getName() = 0;
    //virtual QString getUltimateSkill() = 0;

    //virtual QString getRace() = 0;
    //virtual QString getKind() = 0;
    virtual QString getAllAttritubeInfo();
protected:
    /*pokemon's attribute*/
    QString name;
    unsigned int level;
    unsigned int exp;
    unsigned int cur_exp;
    unsigned int base_attack; //基础攻击力
    unsigned int defense_power; //基础防御力
    unsigned int max_hp; //最大生命值
    unsigned int battle_hp; //当前生命值
    double wsp; //攻击速度
    double battle_wsp; //战斗时攻速,收对方技能影响
    double avoid; //回避率
    double critical; //暴击率

    //pokemonKind kind; //精灵种类
    Rarity rarity; //稀有度
    BaseSkill baseSkill; //基础技能技能
    //UltimateSkill ultimateSkill;//终极技能
    //Race race; //种类

    void setBaseSkill();
    void setRarity();
    virtual void levelUp() = 0;
    //virtual void setRarity(){}
    //virtual void setRace(){}
    //virtual void setUltimateSkill(){}
    virtual void initPokemon();
    void setBaseAttribute(unsigned int _base_attack,
                              unsigned int _defense_power,
                              unsigned int _max_hp,
                              double _wsp,
                              double _avoid,
                              double _critical);

};
