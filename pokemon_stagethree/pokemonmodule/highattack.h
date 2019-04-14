#pragma once

#ifndef HIGHATTACK_H
#define HIGHATTACK_H

#include "pokemon.h"

//基类pokemon的派生类
//也是抽象类,主要实现了基类的levelup函数
//以及重构了initpokemon初始化精灵函数
class POKEMONMODULESHARED_EXPORT HighAttack : public Pokemon
{
public:
    HighAttack(){ name = "Pokemon_highattack";
                     initPokemon();}
    ~HighAttack() override {}

    //获得精灵的类型, 本类型为高攻击
    QString getKind() override;
protected:
    //精灵升级时调用, 为精灵属性做出改变
    void levelUp() override;

    //初始化精灵属性
    void initPokemon() override;
};

#endif // HIGHATTACK_H
