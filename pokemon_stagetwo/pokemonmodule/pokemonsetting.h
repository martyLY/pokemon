#pragma once

#ifndef POKEMONSETTING_H
#define POKEMONSETTING_H

#include <QMap>
#include <QString>
#include "pokemonmodule_global.h"
#define MAX_LEVEL 15

/*精灵种类*/
enum POKEMONMODULESHARED_EXPORT pokemonKind {
    highAttack = 0,
    highBlood,
    highDefense,
    highSpeed,
};

const POKEMONMODULESHARED_EXPORT QList<QString> POKEMONKIND = {"HighAttack", "HighBlood", "HighDefense", "HighSpeed"};

/*稀有度*/
enum POKEMONMODULESHARED_EXPORT Rarity {
    N = 0, R, SR, SSR, UR,
};

const POKEMONMODULESHARED_EXPORT QList<QString> RARITY = {"N", "R", "SR", "SSR", "UR"};

/*技能*/
enum  POKEMONMODULESHARED_EXPORT BaseSkill
{
    buring = 0,
    frozen,
    bloodsucking,
};

#define BURING_DAMAGE 0.05
#define FROZEN_DAMAGE 0.05
#define FROZEN_TIME 3
const POKEMONMODULESHARED_EXPORT QList<QString> BASESKILL = {"Buring", "Frozen", "BloodSucking"};

/*精灵种类*/
enum POKEMONMODULESHARED_EXPORT Race {
    the_frozen_archer_Ashe = 0,
    the_dark_child_Anne,
    the_crimson_reaper_Vladimir,
};
const POKEMONMODULESHARED_EXPORT QList<QString> RACE = {"The Frozen Archer Ashe",
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

static POKEMONMODULESHARED_EXPORT QMap<QString, double> coForMain {
    {"N",0}, {"U", 0.05}, {"R", 0.06},
    {"SR", 0.08}, {"SSR", 0.1}, {"UR", 0.12},
};

static POKEMONMODULESHARED_EXPORT QMap<QString, double> coForNormal {
    {"N",0}, {"U", 0}, {"R", 0.03},
    {"SR", 0.04}, {"SSR", 0.06}, {"UR", 0.08},
};

#endif // POKEMONSETTING_H
