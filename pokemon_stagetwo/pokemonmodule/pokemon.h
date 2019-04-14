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

//精灵抽象基类,包含精灵的基础属性
//初始化的精灵为等级1
//此类中具有纯虚函数attack,用作精灵间的普通攻击
//以及虚函数getAllAttributeInfo,用作返回精灵的基本信息
//默认精灵名字为"pokemon", 不可以给精灵命名
class POKEMONMODULESHARED_EXPORT Pokemon : QObject
{
    Q_OBJECT
public:
    Pokemon():name("Pokemon"),level(1),exp(100),cur_exp(0){initPokemon();}
    virtual ~Pokemon(){}

    //得到精灵等级
    unsigned int getLevel();

    //获得精灵名字
    QString getPokemonName();

    //提升等级的函数,参数为获得的经验值
    void expUp(uint);

    //攻击的调用函数,返回值为造成的伤害数值和技能组成的QPair
    QPair<unsigned int, BaseSkill> baseAttack();

    //被攻击时的调用函数,参数是以受到的伤害数值和技能组成的QPair
    //返回值为来自别的精灵的攻击是否miss掉
    bool getHurt(QPair<uint, BaseSkill>);

    //获得精灵的所有属性信息
    virtual QJsonObject toJsonAllAttritubeInfo() = 0;

    //纯虚函数, 攻击时调用, 返回值为造成伤害的数值和技能组成的QPair
    //在这个攻击中,有几率进行baseattack和ultimateskill, 不同种族精灵的几率不同
    virtual QPair<uint, BaseSkill> attack() = 0;

    //纯虚函数, 独特的终极技能
    //返回值的伤害是独立计算的, 伤害类型因为不同精灵的baseskill不同而不同
    virtual QPair<uint, BaseSkill> ultimateAttack() = 0;

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

    //纯虚函数,精灵升级时的调用函数
    virtual void levelUp() = 0;

    //虚函数, 初始化精灵属性
    virtual void initPokemon();
};

#endif // POKEMON_H
