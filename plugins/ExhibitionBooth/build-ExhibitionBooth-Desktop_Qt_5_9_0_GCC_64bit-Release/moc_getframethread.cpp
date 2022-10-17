/****************************************************************************
** Meta object code from reading C++ file 'getframethread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../getframethread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getframethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetFrameThread_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetFrameThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetFrameThread_t qt_meta_stringdata_GetFrameThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GetFrameThread"
QT_MOC_LITERAL(1, 15, 14), // "threadFinished"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "openFinished"
QT_MOC_LITERAL(4, 44, 4), // "stop"
QT_MOC_LITERAL(5, 49, 14), // "onWorkFinished"
QT_MOC_LITERAL(6, 64, 1), // "i"
QT_MOC_LITERAL(7, 66, 14) // "onOpenFinished"

    },
    "GetFrameThread\0threadFinished\0\0"
    "openFinished\0stop\0onWorkFinished\0i\0"
    "onOpenFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetFrameThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a /* Public */,
       5,    1,   46,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void GetFrameThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetFrameThread *_t = static_cast<GetFrameThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->threadFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->openFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->stop(); break;
        case 3: _t->onWorkFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onOpenFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GetFrameThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFrameThread::threadFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GetFrameThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFrameThread::openFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GetFrameThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GetFrameThread.data,
      qt_meta_data_GetFrameThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GetFrameThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetFrameThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetFrameThread.stringdata0))
        return static_cast<void*>(const_cast< GetFrameThread*>(this));
    return QObject::qt_metacast(_clname);
}

int GetFrameThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GetFrameThread::threadFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GetFrameThread::openFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
