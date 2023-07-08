/****************************************************************************
** Meta object code from reading C++ file 'blockloader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../blockloader.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blockloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_BlockLoader_t {
    uint offsetsAndSizes[36];
    char stringdata0[12];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[18];
    char stringdata5[20];
    char stringdata6[20];
    char stringdata7[20];
    char stringdata8[20];
    char stringdata9[13];
    char stringdata10[16];
    char stringdata11[15];
    char stringdata12[11];
    char stringdata13[12];
    char stringdata14[16];
    char stringdata15[19];
    char stringdata16[14];
    char stringdata17[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BlockLoader_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BlockLoader_t qt_meta_stringdata_BlockLoader = {
    {
        QT_MOC_LITERAL(0, 11),  // "BlockLoader"
        QT_MOC_LITERAL(12, 18),  // "hero_normal_attack"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 18),  // "hero_critic_attack"
        QT_MOC_LITERAL(51, 17),  // "hero_magic_attack"
        QT_MOC_LITERAL(69, 19),  // "enemy_normal_attack"
        QT_MOC_LITERAL(89, 19),  // "enemy_critic_attack"
        QT_MOC_LITERAL(109, 19),  // "enemy_deadly_attack"
        QT_MOC_LITERAL(129, 19),  // "enemy_fireball_hurt"
        QT_MOC_LITERAL(149, 12),  // "hero_healing"
        QT_MOC_LITERAL(162, 15),  // "hero_get_sheild"
        QT_MOC_LITERAL(178, 14),  // "hero_lava_hurt"
        QT_MOC_LITERAL(193, 10),  // "bomb_clash"
        QT_MOC_LITERAL(204, 11),  // "slime_split"
        QT_MOC_LITERAL(216, 15),  // "bow_shoot_arrow"
        QT_MOC_LITERAL(232, 18),  // "enemy_steal_health"
        QT_MOC_LITERAL(251, 13),  // "generate_dust"
        QT_MOC_LITERAL(265, 13)   // "generate_bone"
    },
    "BlockLoader",
    "hero_normal_attack",
    "",
    "hero_critic_attack",
    "hero_magic_attack",
    "enemy_normal_attack",
    "enemy_critic_attack",
    "enemy_deadly_attack",
    "enemy_fireball_hurt",
    "hero_healing",
    "hero_get_sheild",
    "hero_lava_hurt",
    "bomb_clash",
    "slime_split",
    "bow_shoot_arrow",
    "enemy_steal_health",
    "generate_dust",
    "generate_bone"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BlockLoader[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    0,  111,    2, 0x06,    2 /* Public */,
       4,    0,  112,    2, 0x06,    3 /* Public */,
       5,    0,  113,    2, 0x06,    4 /* Public */,
       6,    0,  114,    2, 0x06,    5 /* Public */,
       7,    0,  115,    2, 0x06,    6 /* Public */,
       8,    0,  116,    2, 0x06,    7 /* Public */,
       9,    0,  117,    2, 0x06,    8 /* Public */,
      10,    0,  118,    2, 0x06,    9 /* Public */,
      11,    0,  119,    2, 0x06,   10 /* Public */,
      12,    1,  120,    2, 0x06,   11 /* Public */,
      13,    1,  123,    2, 0x06,   13 /* Public */,
      14,    1,  126,    2, 0x06,   15 /* Public */,
      15,    0,  129,    2, 0x06,   17 /* Public */,
      16,    1,  130,    2, 0x06,   18 /* Public */,
      17,    1,  133,    2, 0x06,   20 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject BlockLoader::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_BlockLoader.offsetsAndSizes,
    qt_meta_data_BlockLoader,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BlockLoader_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BlockLoader, std::true_type>,
        // method 'hero_normal_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hero_critic_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hero_magic_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enemy_normal_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enemy_critic_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enemy_deadly_attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enemy_fireball_hurt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hero_healing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hero_get_sheild'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hero_lava_hurt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'bomb_clash'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'slime_split'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'bow_shoot_arrow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'enemy_steal_health'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generate_dust'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'generate_bone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void BlockLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BlockLoader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->hero_normal_attack(); break;
        case 1: _t->hero_critic_attack(); break;
        case 2: _t->hero_magic_attack(); break;
        case 3: _t->enemy_normal_attack(); break;
        case 4: _t->enemy_critic_attack(); break;
        case 5: _t->enemy_deadly_attack(); break;
        case 6: _t->enemy_fireball_hurt(); break;
        case 7: _t->hero_healing(); break;
        case 8: _t->hero_get_sheild(); break;
        case 9: _t->hero_lava_hurt(); break;
        case 10: _t->bomb_clash((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->slime_split((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->bow_shoot_arrow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->enemy_steal_health(); break;
        case 14: _t->generate_dust((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->generate_bone((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_normal_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_critic_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_magic_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::enemy_normal_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::enemy_critic_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::enemy_deadly_attack; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::enemy_fireball_hurt; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_healing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_get_sheild; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::hero_lava_hurt; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)(int );
            if (_t _q_method = &BlockLoader::bomb_clash; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)(int );
            if (_t _q_method = &BlockLoader::slime_split; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)(int );
            if (_t _q_method = &BlockLoader::bow_shoot_arrow; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)();
            if (_t _q_method = &BlockLoader::enemy_steal_health; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)(int );
            if (_t _q_method = &BlockLoader::generate_dust; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (BlockLoader::*)(int );
            if (_t _q_method = &BlockLoader::generate_bone; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
    }
}

const QMetaObject *BlockLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BlockLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BlockLoader.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int BlockLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void BlockLoader::hero_normal_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BlockLoader::hero_critic_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BlockLoader::hero_magic_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BlockLoader::enemy_normal_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BlockLoader::enemy_critic_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BlockLoader::enemy_deadly_attack()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BlockLoader::enemy_fireball_hurt()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void BlockLoader::hero_healing()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void BlockLoader::hero_get_sheild()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void BlockLoader::hero_lava_hurt()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void BlockLoader::bomb_clash(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void BlockLoader::slime_split(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void BlockLoader::bow_shoot_arrow(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void BlockLoader::enemy_steal_health()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void BlockLoader::generate_dust(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void BlockLoader::generate_bone(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
