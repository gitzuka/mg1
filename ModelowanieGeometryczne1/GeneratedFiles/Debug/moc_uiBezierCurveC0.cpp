/****************************************************************************
** Meta object code from reading C++ file 'uiBezierCurveC0.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uiBezierCurveC0.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiBezierCurveC0.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiBezierCurveC0_t {
    QByteArrayData data[20];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiBezierCurveC0_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiBezierCurveC0_t qt_meta_stringdata_UiBezierCurveC0 = {
    {
QT_MOC_LITERAL(0, 0, 15), // "UiBezierCurveC0"
QT_MOC_LITERAL(1, 16, 10), // "pointAdded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "id"
QT_MOC_LITERAL(4, 31, 12), // "pointRemoved"
QT_MOC_LITERAL(5, 44, 11), // "nameChanged"
QT_MOC_LITERAL(6, 56, 4), // "name"
QT_MOC_LITERAL(7, 61, 18), // "requestedPointsIds"
QT_MOC_LITERAL(8, 80, 32), // "QList<std::shared_ptr<Point3D> >"
QT_MOC_LITERAL(9, 113, 6), // "points"
QT_MOC_LITERAL(10, 120, 12), // "curveDeleted"
QT_MOC_LITERAL(11, 133, 7), // "curveId"
QT_MOC_LITERAL(12, 141, 8), // "addPoint"
QT_MOC_LITERAL(13, 150, 11), // "removePoint"
QT_MOC_LITERAL(14, 162, 10), // "changeName"
QT_MOC_LITERAL(15, 173, 11), // "updateCurve"
QT_MOC_LITERAL(16, 185, 16), // "updateScreenSize"
QT_MOC_LITERAL(17, 202, 5), // "width"
QT_MOC_LITERAL(18, 208, 6), // "height"
QT_MOC_LITERAL(19, 215, 12) // "getPointsIds"

    },
    "UiBezierCurveC0\0pointAdded\0\0id\0"
    "pointRemoved\0nameChanged\0name\0"
    "requestedPointsIds\0QList<std::shared_ptr<Point3D> >\0"
    "points\0curveDeleted\0curveId\0addPoint\0"
    "removePoint\0changeName\0updateCurve\0"
    "updateScreenSize\0width\0height\0"
    "getPointsIds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiBezierCurveC0[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    2,   75,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,
      10,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   86,    2, 0x0a /* Public */,
      13,    1,   89,    2, 0x0a /* Public */,
      14,    2,   92,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      16,    2,   98,    2, 0x0a /* Public */,
      19,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    6,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   17,   18,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void UiBezierCurveC0::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiBezierCurveC0 *_t = static_cast<UiBezierCurveC0 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pointAdded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->pointRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->nameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->requestedPointsIds((*reinterpret_cast< const QList<std::shared_ptr<Point3D> >(*)>(_a[1]))); break;
        case 4: _t->curveDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->addPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->removePoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->updateCurve(); break;
        case 9: _t->updateScreenSize((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 10: _t->getPointsIds((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UiBezierCurveC0::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::pointAdded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::pointRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::nameChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(const QList<std::shared_ptr<Point3D>> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::requestedPointsIds)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::curveDeleted)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject UiBezierCurveC0::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UiBezierCurveC0.data,
      qt_meta_data_UiBezierCurveC0,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UiBezierCurveC0::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiBezierCurveC0::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UiBezierCurveC0.stringdata0))
        return static_cast<void*>(const_cast< UiBezierCurveC0*>(this));
    return QObject::qt_metacast(_clname);
}

int UiBezierCurveC0::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void UiBezierCurveC0::pointAdded(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UiBezierCurveC0::pointRemoved(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiBezierCurveC0::nameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UiBezierCurveC0::requestedPointsIds(const QList<std::shared_ptr<Point3D>> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UiBezierCurveC0::curveDeleted(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
