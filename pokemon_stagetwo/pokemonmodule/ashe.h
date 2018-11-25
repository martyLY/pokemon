#pragma once

#ifndef ASHE_H
#define ASHE_H

#include "highattack.h"
class POKEMONMODULESHARED_EXPORT Ashe : public HighAttack
{
public:
    Ashe(QString _name){name = _name;race = the_frozen_archer_Ashe;
                            initPokemon();}
    Ashe(QJsonDocument &);
    QString getRace() override;
    QJsonObject toJsonAllAttritubeInfo() override;

protected:
    //Race race;
};

#endif // ASHE_H
