/****************************************************************************
** Meta object code from reading C++ file 'db_custompushbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CustomWidget/db_custompushbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'db_custompushbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DB_CustomPushButton_2_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DB_CustomPushButton_2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DB_CustomPushButton_2_t qt_meta_stringdata_DB_CustomPushButton_2 = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DB_CustomPushButton_2"
QT_MOC_LITERAL(1, 22, 12), // "mouseClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15), // "mouseDblClicked"
QT_MOC_LITERAL(4, 52, 14), // "checkedClicked"
QT_MOC_LITERAL(5, 67, 16) // "uncheckedClicked"

    },
    "DB_CustomPushButton_2\0mouseClicked\0\0"
    "mouseDblClicked\0checkedClicked\0"
    "uncheckedClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DB_CustomPushButton_2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DB_CustomPushButton_2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DB_CustomPushButton_2 *_t = static_cast<DB_CustomPushButton_2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseClicked(); break;
        case 1: _t->mouseDblClicked(); break;
        case 2: _t->checkedClicked(); break;
        case 3: _t->uncheckedClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DB_CustomPushButton_2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_CustomPushButton_2::mouseClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DB_CustomPushButton_2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_CustomPushButton_2::mouseDblClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DB_CustomPushButton_2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_CustomPushButton_2::checkedClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DB_CustomPushButton_2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_CustomPushButton_2::uncheckedClicked)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DB_CustomPushButton_2::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_DB_CustomPushButton_2.data,
      qt_meta_data_DB_CustomPushButton_2,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DB_CustomPushButton_2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_CustomPushButton_2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DB_CustomPushButton_2.stringdata0))
        return static_cast<void*>(const_cast< DB_CustomPushButton_2*>(this));
    return QPushButton::qt_metacast(_clname);
}

int DB_CustomPushButton_2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DB_CustomPushButton_2::mouseClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DB_CustomPushButton_2::mouseDblClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DB_CustomPushButton_2::checkedClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DB_CustomPushButton_2::uncheckedClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_DB_CustomPushButton_3_t {
    QByteArrayData data[1];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DB_CustomPushButton_3_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DB_CustomPushButton_3_t qt_meta_stringdata_DB_CustomPushButton_3 = {
    {
QT_MOC_LITERAL(0, 0, 21) // "DB_CustomPushButton_3"

    },
    "DB_CustomPushButton_3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DB_CustomPushButton_3[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DB_CustomPushButton_3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject DB_CustomPushButton_3::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_DB_CustomPushButton_3.data,
      qt_meta_data_DB_CustomPushButton_3,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DB_CustomPushButton_3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_CustomPushButton_3::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DB_CustomPushButton_3.stringdata0))
        return static_cast<void*>(const_cast< DB_CustomPushButton_3*>(this));
    return QPushButton::qt_metacast(_clname);
}

int DB_CustomPushButton_3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DB_CustomPushButton_4_t {
    QByteArrayData data[1];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DB_CustomPushButton_4_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DB_CustomPushButton_4_t qt_meta_stringdata_DB_CustomPushButton_4 = {
    {
QT_MOC_LITERAL(0, 0, 21) // "DB_CustomPushButton_4"

    },
    "DB_CustomPushButton_4"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DB_CustomPushButton_4[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DB_CustomPushButton_4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject DB_CustomPushButton_4::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_DB_CustomPushButton_4.data,
      qt_meta_data_DB_CustomPushButton_4,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DB_CustomPushButton_4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_CustomPushButton_4::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DB_CustomPushButton_4.stringdata0))
        return static_cast<void*>(const_cast< DB_CustomPushButton_4*>(this));
    return QPushButton::qt_metacast(_clname);
}

int DB_CustomPushButton_4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
