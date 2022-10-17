/****************************************************************************
** Meta object code from reading C++ file 'db_exhibitionbooth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../db_exhibitionbooth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'db_exhibitionbooth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DB_ExhibitionBooth_t {
    QByteArrayData data[21];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DB_ExhibitionBooth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DB_ExhibitionBooth_t qt_meta_stringdata_DB_ExhibitionBooth = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DB_ExhibitionBooth"
QT_MOC_LITERAL(1, 19, 21), // "exhibitionBoothClosed"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 12), // "displayImage"
QT_MOC_LITERAL(4, 55, 16), // "deviceDisconnect"
QT_MOC_LITERAL(5, 72, 13), // "showOneScreen"
QT_MOC_LITERAL(6, 86, 13), // "showTwoScreen"
QT_MOC_LITERAL(7, 100, 14), // "showFourScreen"
QT_MOC_LITERAL(8, 115, 22), // "onResolutionBtnClicked"
QT_MOC_LITERAL(9, 138, 15), // "onWindowChecked"
QT_MOC_LITERAL(10, 154, 22), // "onWindowShowFullScreen"
QT_MOC_LITERAL(11, 177, 11), // "screenShots"
QT_MOC_LITERAL(12, 189, 4), // "rect"
QT_MOC_LITERAL(13, 194, 13), // "onTakingPhoto"
QT_MOC_LITERAL(14, 208, 17), // "onShowCameraFrame"
QT_MOC_LITERAL(15, 226, 2), // "bo"
QT_MOC_LITERAL(16, 229, 8), // "QWidget*"
QT_MOC_LITERAL(17, 238, 6), // "widget"
QT_MOC_LITERAL(18, 245, 6), // "pixmap"
QT_MOC_LITERAL(19, 252, 14), // "onCameraClosed"
QT_MOC_LITERAL(20, 267, 3) // "ret"

    },
    "DB_ExhibitionBooth\0exhibitionBoothClosed\0"
    "\0displayImage\0deviceDisconnect\0"
    "showOneScreen\0showTwoScreen\0showFourScreen\0"
    "onResolutionBtnClicked\0onWindowChecked\0"
    "onWindowShowFullScreen\0screenShots\0"
    "rect\0onTakingPhoto\0onShowCameraFrame\0"
    "bo\0QWidget*\0widget\0pixmap\0onCameraClosed\0"
    "ret"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DB_ExhibitionBooth[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   81,    2, 0x08 /* Private */,
       5,    0,   84,    2, 0x08 /* Private */,
       6,    0,   85,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    1,   90,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    3,   94,    2, 0x08 /* Private */,
      19,    1,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRectF,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 16, QMetaType::QPixmap,   15,   17,   18,
    QMetaType::Void, QMetaType::Int,   20,

       0        // eod
};

void DB_ExhibitionBooth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DB_ExhibitionBooth *_t = static_cast<DB_ExhibitionBooth *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->exhibitionBoothClosed(); break;
        case 1: _t->displayImage(); break;
        case 2: _t->deviceDisconnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->showOneScreen(); break;
        case 4: _t->showTwoScreen(); break;
        case 5: _t->showFourScreen(); break;
        case 6: _t->onResolutionBtnClicked(); break;
        case 7: _t->onWindowChecked(); break;
        case 8: _t->onWindowShowFullScreen(); break;
        case 9: _t->screenShots((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 10: _t->onTakingPhoto(); break;
        case 11: _t->onShowCameraFrame((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])),(*reinterpret_cast< QPixmap(*)>(_a[3]))); break;
        case 12: _t->onCameraClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DB_ExhibitionBooth::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_ExhibitionBooth::exhibitionBoothClosed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DB_ExhibitionBooth::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DB_ExhibitionBooth::displayImage)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DB_ExhibitionBooth::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DB_ExhibitionBooth.data,
      qt_meta_data_DB_ExhibitionBooth,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DB_ExhibitionBooth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_ExhibitionBooth::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DB_ExhibitionBooth.stringdata0))
        return static_cast<void*>(const_cast< DB_ExhibitionBooth*>(this));
    return QWidget::qt_metacast(_clname);
}

int DB_ExhibitionBooth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DB_ExhibitionBooth::exhibitionBoothClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DB_ExhibitionBooth::displayImage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
