#ifndef GLOBAL_H
#define GLOBAL_H

#include <QHostAddress>

#include "pokemonmodule_global.h"
#include "ashe.h"
#include "anne.h"
#include "vladimir.h"

enum POKEMONMODULESHARED_EXPORT datatype : int{
    login,
    loginyes,
    loginno,
    loginrepeat,
    signup,
    signupyes,
    signupno,
    signuprepeat,
    close,
    onlineusradd,
    onlineusrerase,
    matchfight,
    fightaddr,
    win,
    lose,
    redattack,
    blueattack,
    losepokemon,
    winpokemon,
    stillonline,
};

enum POKEMONMODULESHARED_EXPORT Pagename {
    startmenu,
    signuppage,
    mainpage,
};

extern POKEMONMODULESHARED_EXPORT QHostAddress serverAddr;
extern POKEMONMODULESHARED_EXPORT quint16 port;
#endif // GLOBAL_H
