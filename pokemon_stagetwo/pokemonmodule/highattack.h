#pragma once

#ifndef HIGHATTACK_H
#define HIGHATTACK_H

#include "pokemon.h"

/*高攻击力的初始属性值*/
const unsigned int BASEATTACK = 200;
const unsigned int DEFENSEPOWER = 80;
const unsigned int MAXHP = 100;
const double WSP = 0.7;
const double AVOID = 0.08;
const double CRITICAL = 0.1;

/*升级属性增长系数*/
const double coLevelupMain = 0.05;
const double coLevelupNormal = 0.02;

class POKEMONMODULESHARED_EXPORT HighAttack : public Pokemon
{
public:
    HighAttack(){name = "Pokemon_highattack";initPokemon();}
    ~HighAttack() override {}

    QString getKind() override;

protected:
    //pokemonKind kind;
    void levelUp() override;
    void initPokemon() override;

};

#endif // HIGHATTACK_H
