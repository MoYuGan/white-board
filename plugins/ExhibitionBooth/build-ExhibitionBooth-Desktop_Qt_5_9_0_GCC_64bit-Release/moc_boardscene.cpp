/****************************************************************************
** Meta object code from reading C++ file 'boardscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../boardscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boardscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BoardScene_t {
    QByteArrayData data[12];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BoardScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BoardScene_t qt_meta_stringdata_BoardScene = {
    {
QT_MOC_LITERAL(0, 0, 10), // "BoardScene"
QT_MOC_LITERAL(1, 11, 11), // "rotateItems"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "angle"
QT_MOC_LITERAL(4, 30, 6), // "center"
QT_MOC_LITERAL(5, 37, 10), // "scaleItems"
QT_MOC_LITERAL(6, 48, 7), // "xFactor"
QT_MOC_LITERAL(7, 56, 7), // "yFactor"
QT_MOC_LITERAL(8, 64, 9), // "direction"
QT_MOC_LITERAL(9, 74, 10), // "fixedPoint"
QT_MOC_LITERAL(10, 85, 11), // "loadPicture"
QT_MOC_LITERAL(11, 97, 8) // "fileName"

    },
    "BoardScene\0rotateItems\0\0angle\0center\0"
    "scaleItems\0xFactor\0yFactor\0direction\0"
    "fixedPoint\0loadPicture\0fileName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BoardScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x0a /* Public */,
       5,    4,   34,    2, 0x0a /* Public */,
      10,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::QPointF,    3,    4,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::Int, QMetaType::QPointF,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void BoardScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BoardScene *_t = static_cast<BoardScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rotateItems((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 1: _t->scaleItems((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QPointF(*)>(_a[4]))); break;
        case 2: _t->loadPicture((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BoardScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_BoardScene.data,
      qt_meta_data_BoardScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BoardScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BoardScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BoardScene.stringdata0))
        return static_cast<void*>(const_cast< BoardScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int BoardScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
