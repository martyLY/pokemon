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
    signup,
    signupyes,
    signupno,
    signuprepeat,
    close,
    onlineusradd,
    onlineusrerase,
};

enum POKEMONMODULESHARED_EXPORT Pagename {
    startmenu,
    signuppage,
    mainpage,
};

extern POKEMONMODULESHARED_EXPORT QHostAddress serverAddr;
extern POKEMONMODULESHARED_EXPORT quint16 port;
#endif // GLOBAL_H
