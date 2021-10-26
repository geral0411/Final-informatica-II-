/****************************************************************************
** Meta object code from reading C++ file 'mundos.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Proyecto/mundos.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mundos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mundos_t {
    QByteArrayData data[18];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mundos_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mundos_t qt_meta_stringdata_Mundos = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Mundos"
QT_MOC_LITERAL(1, 7, 17), // "jumpFactorChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "jumpPersonaje"
QT_MOC_LITERAL(4, 40, 17), // "jumpStatusChanged"
QT_MOC_LITERAL(5, 58, 25), // "QAbstractAnimation::State"
QT_MOC_LITERAL(6, 84, 8), // "newState"
QT_MOC_LITERAL(7, 93, 8), // "oldState"
QT_MOC_LITERAL(8, 102, 14), // "moverPersonaje"
QT_MOC_LITERAL(9, 117, 13), // "fallPersonaje"
QT_MOC_LITERAL(10, 131, 16), // "manejoColisiones"
QT_MOC_LITERAL(11, 148, 18), // "checkColisionMuros"
QT_MOC_LITERAL(12, 167, 14), // "checkColNueces"
QT_MOC_LITERAL(13, 182, 6), // "Estado"
QT_MOC_LITERAL(14, 189, 1), // "n"
QT_MOC_LITERAL(15, 191, 18), // "collidingPlatforms"
QT_MOC_LITERAL(16, 210, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(17, 225, 10) // "jumpFactor"

    },
    "Mundos\0jumpFactorChanged\0\0jumpPersonaje\0"
    "jumpStatusChanged\0QAbstractAnimation::State\0"
    "newState\0oldState\0moverPersonaje\0"
    "fallPersonaje\0manejoColisiones\0"
    "checkColisionMuros\0checkColNueces\0"
    "Estado\0n\0collidingPlatforms\0QGraphicsItem*\0"
    "jumpFactor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mundos[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       1,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   67,    2, 0x08 /* Private */,
       4,    2,   68,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    0,   76,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    1,   78,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    0x80000000 | 16,

 // properties: name, type, flags
      17, QMetaType::QReal, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void Mundos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mundos *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jumpFactorChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->jumpPersonaje(); break;
        case 2: _t->jumpStatusChanged((*reinterpret_cast< QAbstractAnimation::State(*)>(_a[1])),(*reinterpret_cast< QAbstractAnimation::State(*)>(_a[2]))); break;
        case 3: _t->moverPersonaje(); break;
        case 4: _t->fallPersonaje(); break;
        case 5: { bool _r = _t->manejoColisiones();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->checkColisionMuros(); break;
        case 7: _t->checkColNueces(); break;
        case 8: _t->Estado((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: { QGraphicsItem* _r = _t->collidingPlatforms();
            if (_a[0]) *reinterpret_cast< QGraphicsItem**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mundos::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mundos::jumpFactorChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Mundos *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->jumpFactor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Mundos *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setJumpFactor(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Mundos::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_Mundos.data,
    qt_meta_data_Mundos,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Mundos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mundos::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mundos.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int Mundos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Mundos::jumpFactorChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
