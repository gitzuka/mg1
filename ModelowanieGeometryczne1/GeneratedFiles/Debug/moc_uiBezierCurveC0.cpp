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
    QByteArrayData data[22];
    char stringdata0[246];
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
QT_MOC_LITERAL(4, 31, 11), // "nameChanged"
QT_MOC_LITERAL(5, 43, 4), // "name"
QT_MOC_LITERAL(6, 48, 15), // "requestedPoints"
QT_MOC_LITERAL(7, 64, 32), // "QList<std::shared_ptr<Point3D> >"
QT_MOC_LITERAL(8, 97, 6), // "points"
QT_MOC_LITERAL(9, 104, 12), // "curveDeleted"
QT_MOC_LITERAL(10, 117, 7), // "curveId"
QT_MOC_LITERAL(11, 125, 8), // "addPoint"
QT_MOC_LITERAL(12, 134, 7), // "pointId"
QT_MOC_LITERAL(13, 142, 11), // "removePoint"
QT_MOC_LITERAL(14, 154, 10), // "changeName"
QT_MOC_LITERAL(15, 165, 11), // "updateCurve"
QT_MOC_LITERAL(16, 177, 16), // "updateScreenSize"
QT_MOC_LITERAL(17, 194, 5), // "width"
QT_MOC_LITERAL(18, 200, 6), // "height"
QT_MOC_LITERAL(19, 207, 12), // "getPointsIds"
QT_MOC_LITERAL(20, 220, 19), // "changePolylineState"
QT_MOC_LITERAL(21, 240, 5) // "state"

    },
    "UiBezierCurveC0\0pointAdded\0\0id\0"
    "nameChanged\0name\0requestedPoints\0"
    "QList<std::shared_ptr<Point3D> >\0"
    "points\0curveDeleted\0curveId\0addPoint\0"
    "pointId\0removePoint\0changeName\0"
    "updateCurve\0updateScreenSize\0width\0"
    "height\0getPointsIds\0changePolylineState\0"
    "state"
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
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       6,    1,   77,    2, 0x06 /* Public */,
       9,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   83,    2, 0x0a /* Public */,
      13,    2,   88,    2, 0x0a /* Public */,
      14,    2,   93,    2, 0x0a /* Public */,
      15,    0,   98,    2, 0x0a /* Public */,
      16,    2,   99,    2, 0x0a /* Public */,
      19,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   17,   18,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void UiBezierCurveC0::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiBezierCurveC0 *_t = static_cast<UiBezierCurveC0 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pointAdded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->nameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->requestedPoints((*reinterpret_cast< const QList<std::shared_ptr<Point3D> >(*)>(_a[1]))); break;
        case 3: _t->curveDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->addPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->removePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->changeName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->updateCurve(); break;
        case 8: _t->updateScreenSize((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->getPointsIds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changePolylineState((*reinterpret_cast< int(*)>(_a[1]))); break;
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
            typedef void (UiBezierCurveC0::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::nameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(const QList<std::shared_ptr<Point3D>> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::requestedPoints)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC0::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC0::curveDeleted)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject UiBezierCurveC0::staticMetaObject = {
    { &UiConnector::staticMetaObject, qt_meta_stringdata_UiBezierCurveC0.data,
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
    return UiConnector::qt_metacast(_clname);
}

int UiBezierCurveC0::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UiConnector::qt_metacall(_c, _id, _a);
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
void UiBezierCurveC0::nameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiBezierCurveC0::requestedPoints(const QList<std::shared_ptr<Point3D>> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UiBezierCurveC0::curveDeleted(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
