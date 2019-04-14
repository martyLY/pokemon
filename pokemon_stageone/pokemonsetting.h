//本头文件包含所有精灵的种族, 类型, 稀有度等选择,以及对应的字符串表示
//并且包括精灵用到的比如伤害系数,或者是升级用的成长系数

#ifndef POKEMONSETTING_H
#define POKEMONSETTING_H

#include <QMap>
#include <QString>

//最大等级设定
#define MAX_LEVEL 15

//精灵类型
enum pokemonKind {
    highAttack = 0,
    highBlood,
    highDefense,
    highSpeed,
};

//对应枚举类的类型字符串
const QList<QString> POKEMONKIND = {"HighAttack", "HighBlood", "HighDefense", "HighSpeed"};

//稀有度
enum Rarity {
    N = 0, R, SR, SSR, UR,
};

//对应枚举类的稀有度字符串
const QList<QString> RARITY = {"N", "R", "SR", "SSR", "UR"};

//技能
enum BaseSkill
{
    buring = 0,
    frozen,
    bloodsucking,
    none,
};

//技能伤害,次数定义
#define BURING_DAMAGE 0.05  //灼烧技能造成伤害系数
#define FROZEN_DAMAGE 0.05  //冰冻技能造成伤害系数
#define FROZEN_TIME 3  //最大冰冻技能发动次数

//对应枚举类的技能字符串
const QList<QString> BASESKILL = {"Buring", "Frozen", "BloodSucking", "None"};

//精灵种族
enum Race {
    the_frozen_archer_Ashe = 0,
    the_dark_child_Anne,
    the_crimson_reaper_Vladimir,
};

//对应枚举类的中速字符串
const QList<QString> RACE = {"The Frozen Archer Ashe",
                                 "The Dark Child Anne",
                                 "The Crimson Reaper Vladimir"};

//对于主属性增长,不同稀有度的属性基础乘积系数
static QMap<QString, double> coForMain {
    {"N",0}, {"U", 0.05}, {"R", 0.06},
    {"SR", 0.08}, {"SSR", 0.1}, {"UR", 0.12},
};

//对于其他属性, 不同稀有度的属性基础乘积系数
static QMap<QString, double> coForNormal {
    {"N",0}, {"U", 0}, {"R", 0.03},
    {"SR", 0.04}, {"SSR", 0.06}, {"UR", 0.08},
};

#endif // POKEMONSETTING_H
