#ifndef GLOBAL_H
#define GLOBAL_H

#include <QHostAddress>

enum datatype : int{
    login,
    loginyes,
    loginno,
    signup,
    signupyes,
    signupno,
    signuprepeat,
};

enum Pagename {
    startmenu,
    signuppage,q
    mainpage,
};

extern QHostAddress serverAddr;
extern quint16 port;
#endif // GLOBAL_H
