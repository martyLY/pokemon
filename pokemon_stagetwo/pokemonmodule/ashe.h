#ifndef ASHE_H
#define ASHE_H

#include "highattack.h"
class POKEMONMODULESHARED_EXPORT Ashe : public HighAttack
{
public:
    Ashe(QString _name){name = _name;race = the_frozen_archer_Ashe;
                            initPokemon();}
    QString getRace();
    QString getAllAttritubeInfo() override;

protected:
    Race race;
    //void initPokemon() override;
};

#endif // ASHE_H
