/****************************************************************************
** Meta object code from reading C++ file 'pokemonchoose.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PokemonClient/pokemonchoose.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pokemonchoose.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pokemonChoose_t {
    QByteArrayData data[6];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pokemonChoose_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pokemonChoose_t qt_meta_stringdata_pokemonChoose = {
    {
QT_MOC_LITERAL(0, 0, 13), // "pokemonChoose"
QT_MOC_LITERAL(1, 14, 14), // "choosedPokemon"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "pokemonHasChoosed"
QT_MOC_LITERAL(4, 48, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(5, 65, 23) // "deadFightChoosedPokemon"

    },
    "pokemonChoose\0choosedPokemon\0\0"
    "pokemonHasChoosed\0QListWidgetItem*\0"
    "deadFightChoosedPokemon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pokemonChoose[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   32,    2, 0x08 /* Private */,
       5,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void pokemonChoose::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pokemonChoose *_t = static_cast<pokemonChoose *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choosedPokemon((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pokemonHasChoosed((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->deadFightChoosedPokemon((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pokemonChoose::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pokemonChoose::choosedPokemon)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pokemonChoose::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_pokemonChoose.data,
      qt_meta_data_pokemonChoose,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *pokemonChoose::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pokemonChoose::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pokemonChoose.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pokemonChoose::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void pokemonChoose::choosedPokemon(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
