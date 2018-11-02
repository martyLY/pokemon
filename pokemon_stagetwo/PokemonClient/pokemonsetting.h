#ifndef POKEMONSETTING_H
#define POKEMONSETTING_H

#include <QMap>
#include <QString>

#endif // POKEMONSETTING_H

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

#define BURING_DAMAGE 0.05
#define FROZEN_DAMAGE 0.05
#define FROZEN_TIME 3
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
