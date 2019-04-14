#ifndef HIGHDEFENSE_H
#define HIGHDEFENSE_H

#include <QObject>
#include "pokemon.h"

//基类pokemon的派生类
//也是抽象类,主要实现了基类的levelup函数
//以及重构了initpokemon初始化精灵函数
class HighDefense : public Pokemon
{
public:
    HighDefense(){ name = "Pokemon_highdefense";
                     initPokemon();}
    ~HighDefense() override {}

    //获得精灵的类型, 本类型为高攻击
    QString getKind() override;

protected:
    //精灵类型
    pokemonKind kind;

    //精灵升级时调用, 为精灵属性做出改变
    void levelUp() override;

    //初始化精灵属性
    void initPokemon() override;

};

#endif // HIGHDEFENSE_H
