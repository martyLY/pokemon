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

#define MAX_LEVEL 15

/*精灵种类*/
enum pokemonKind {
    highAttack = 0,
    highBlood,
    highDefense,
    highSpeed,
};

const QList<QString> POKEMONKIND = {"HighAttack", "HighBlood", "HighDefense", "HighSpeed"};

/*稀有度*/
enum Rarity {
    N = 0, R, SR, SSR, UR,
};

const QList<QString> RARITY = {"N", "R", "SR", "SSR", "UR"};

/*技能*/
enum BaseSkill
{
    buring = 0,
    frozen,
    bloodsucking,
};

const QList<QString> BASESKILL = {"Buring", "Frozen", "BloodSucking"};

/*精灵种类*/
enum Race {
    the_frozen_archer_Ashe = 0,
    the_dark_child_Anne,
    the_crimson_reaper_Vladimir,
};
const QList<QString> RACE = {"The Frozen Archer Ashe",
                             "The Dark Child Anne",
                             "The Crimson Reaper Vladimir"};

/*不同稀有度的属性基础乘积系数*/
/*
const double UForMain = 0.05;
const double RForMain = 0.1;
const double SRForMain = 0.3;
const double SSRForMain = 0.8;
const double URForMain = 1.0;

const double UForNormal = 0;
const double RForNormal = 0.03;
const double SRForNormal = 0.1;
const double SSRForNormal = 0.15;
const double URForNormal = 0.2;
*/

static QMap<QString, double> coForMain {
    {"N",0}, {"U", 0.05}, {"R", 0.06},
    {"SR", 0.08}, {"SSR", 0.1}, {"UR", 0.12},
};

static QMap<QString, double> coForNormal {
    {"N",0}, {"U", 0}, {"R", 0.03},
    {"SR", 0.04}, {"SSR", 0.06}, {"UR", 0.08},
};


class Pokemon : public QObject
{
    Q_OBJECT
public:
    Pokemon():level(1),cur_exp(0),exp(100){}
    virtual ~Pokemon(){}

    QString getName();
    QString getAllAttritubeInfo();
    unsigned int getLevel();
    void expUp(unsigned int exp);
    virtual QString getRace() = 0;
    //virtual QString getUltimateSkill() = 0;


    virtual void levelUp(){}
    virtual QPair<unsigned int, BaseSkill> Attack() = 0;
    virtual void getHurt(QPair<unsigned int, BaseSkill> damage) = 0;
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
    double avoid; //回避率
    double critical; //暴击率

    pokemonKind kind; //精灵种类
    Rarity rarity; //稀有度
    BaseSkill baseSkill; //基础技能技能
    Race race; //种类

    void setBaseSkill();
    void setRarity();

    //virtual void setRarity(){}
    virtual void setRace(){}
    //virtual void setUltimateSkill(){}
    virtual void setBaseAttribute(unsigned int _base_attack,
                                  unsigned int _defense_power,
                                  unsigned int _max_hp,
                                  double _wsp,
                                  double _avoid,
                                  double _critical) {}

};
