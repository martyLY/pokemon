#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QRandomGenerator>
#include <QDebug>
#include <QtGlobal>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include "pokemonsetting.h"
#include "damageinfo.h"

class POKEMONMODULESHARED_EXPORT Pokemon : public QObject
{
    Q_OBJECT
public:
    Pokemon():name("Pokemon"),level(1),exp(100),cur_exp(0){initPokemon();}
    virtual ~Pokemon(){}

    //提升等级的函数,参数为获得的经验值
    void expUp(uint exp);

    //设置精灵等级,一般不调用, 当生成特定等级精灵时调用
    void setLevel(uint);

    //进入战斗模式, 将精灵属性数据赋值给战斗时的数据
    void setBattleMode();

    //设置精灵名字
    void setPokemonName(QString);

    //获得攻速
    double getWsp() {return  wsp;}

    //获得战斗时血量
    uint getBattleHp() {return battle_hp;}

    //得到精灵等级
    uint getLevel();

    //获得精灵名字
    QString getPokemonName();

    //攻击的调用函数,返回值为造成的伤害数值和技能组成伤害类
    DamageInfo baseAttack();

    //虚函数, 攻击时调用, 返回值为造成伤害的数值和技能组成的QPair
    //在这个攻击中,有几率进行baseattack和ultimateskill, 不同种族精灵的几率不同
    virtual DamageInfo Attack();

    //虚函数,参数为获得的对方的伤害, 造成伤害后返回世纪造成的伤害类
    virtual DamageInfo getHurt(DamageInfo);

    //获得精灵的所有属性信息
    virtual QJsonObject toJsonAllAttritubeInfo() = 0;

    //虚函数, 获得精灵的种族
    virtual QString getRace() = 0;

    //虚函数, 获得精灵类型
    virtual QString getKind() = 0;
protected:
    /*pokemon's attribute*/
    QString name; //精灵名字
    uint level;  //等级
    uint exp;  //升级需要的总经验值
    uint cur_exp;  //当前获得的经验值
    uint base_attack; //基础攻击力
    uint defense_power; //基础防御力
    uint max_hp; //最大生命值
    uint battle_hp; //当前生命值

    double wsp; //攻击速度
    double battle_wsp; //战斗时攻速,收对方技能影响
    double avoid; //回避率
    double critical; //暴击率

    Rarity rarity; //稀有度
    BaseSkill baseSkill; //基础技能技能
    Race race;
    pokemonKind kind;

    //随机设置一个精灵基础技能
    void setBaseSkill();

    //随机给精灵设置一个稀有度
    void setRarity();

    //为精灵设置参数给定的属性值
    void setBaseAttribute(unsigned int _base_attack,
                              unsigned int _defense_power,
                              unsigned int _max_hp,
                              double _wsp,
                              double _avoid,
                              double _critical);

    virtual void levelUp() = 0;

    //pokemon基类纯虚函数的实现, 精灵进行终极技能攻击
    virtual DamageInfo ultimateSkillAttack() = 0;

    //精灵信息初始化
    virtual void initPokemon();

signals:
    void pokemonDead();

};

#endif // POKEMON_H
