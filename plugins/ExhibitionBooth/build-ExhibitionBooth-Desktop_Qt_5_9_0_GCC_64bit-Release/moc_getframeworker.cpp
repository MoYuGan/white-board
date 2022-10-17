/****************************************************************************
** Meta object code from reading C++ file 'getframeworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../getframeworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getframeworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetFrameWorker_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetFrameWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetFrameWorker_t qt_meta_stringdata_GetFrameWorker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GetFrameWorker"
QT_MOC_LITERAL(1, 15, 12), // "openFinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "workFinished"
QT_MOC_LITERAL(4, 42, 11) // "startWorker"

    },
    "GetFrameWorker\0openFinished\0\0workFinished\0"
    "startWorker"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetFrameWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GetFrameWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetFrameWorker *_t = static_cast<GetFrameWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->workFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->startWorker(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GetFrameWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFrameWorker::openFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GetFrameWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFrameWorker::workFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GetFrameWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GetFrameWorker.data,
      qt_meta_data_GetFrameWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GetFrameWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetFrameWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetFrameWorker.stringdata0))
        return static_cast<void*>(const_cast< GetFrameWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int GetFrameWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void GetFrameWorker::openFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GetFrameWorker::workFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
