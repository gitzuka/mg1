/****************************************************************************
** Meta object code from reading C++ file 'uiBezierCurveC2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uiBezierCurveC2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiBezierCurveC2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiBezierCurveC2_t {
    QByteArrayData data[34];
    char stringdata0[501];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiBezierCurveC2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiBezierCurveC2_t qt_meta_stringdata_UiBezierCurveC2 = {
    {
QT_MOC_LITERAL(0, 0, 15), // "UiBezierCurveC2"
QT_MOC_LITERAL(1, 16, 10), // "pointAdded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "id"
QT_MOC_LITERAL(4, 31, 4), // "name"
QT_MOC_LITERAL(5, 36, 11), // "nameChanged"
QT_MOC_LITERAL(6, 48, 15), // "requestedPoints"
QT_MOC_LITERAL(7, 64, 32), // "QList<std::shared_ptr<Point3D> >"
QT_MOC_LITERAL(8, 97, 6), // "points"
QT_MOC_LITERAL(9, 104, 12), // "curveDeleted"
QT_MOC_LITERAL(10, 117, 7), // "curveId"
QT_MOC_LITERAL(11, 125, 18), // "addedControlPoints"
QT_MOC_LITERAL(12, 144, 38), // "std::vector<std::shared_ptr<P..."
QT_MOC_LITERAL(13, 183, 13), // "controlPoints"
QT_MOC_LITERAL(14, 197, 16), // "std::vector<int>"
QT_MOC_LITERAL(15, 214, 17), // "prevControlPoints"
QT_MOC_LITERAL(16, 232, 21), // "bezierCurve2Destroyed"
QT_MOC_LITERAL(17, 254, 16), // "controlPointsIds"
QT_MOC_LITERAL(18, 271, 12), // "assignPoints"
QT_MOC_LITERAL(19, 284, 45), // "std::vector<std::shared_ptr<D..."
QT_MOC_LITERAL(20, 330, 8), // "addPoint"
QT_MOC_LITERAL(21, 339, 31), // "std::shared_ptr<DrawableObject>"
QT_MOC_LITERAL(22, 371, 5), // "point"
QT_MOC_LITERAL(23, 377, 11), // "removePoint"
QT_MOC_LITERAL(24, 389, 7), // "pointId"
QT_MOC_LITERAL(25, 397, 19), // "changePolylineState"
QT_MOC_LITERAL(26, 417, 5), // "state"
QT_MOC_LITERAL(27, 423, 10), // "changeName"
QT_MOC_LITERAL(28, 434, 11), // "updateCurve"
QT_MOC_LITERAL(29, 446, 16), // "updateScreenSize"
QT_MOC_LITERAL(30, 463, 5), // "width"
QT_MOC_LITERAL(31, 469, 6), // "height"
QT_MOC_LITERAL(32, 476, 12), // "getPointsIds"
QT_MOC_LITERAL(33, 489, 11) // "changeBasis"

    },
    "UiBezierCurveC2\0pointAdded\0\0id\0name\0"
    "nameChanged\0requestedPoints\0"
    "QList<std::shared_ptr<Point3D> >\0"
    "points\0curveDeleted\0curveId\0"
    "addedControlPoints\0"
    "std::vector<std::shared_ptr<Point3D> >\0"
    "controlPoints\0std::vector<int>\0"
    "prevControlPoints\0bezierCurve2Destroyed\0"
    "controlPointsIds\0assignPoints\0"
    "std::vector<std::shared_ptr<DrawableObject> >\0"
    "addPoint\0std::shared_ptr<DrawableObject>\0"
    "point\0removePoint\0pointId\0changePolylineState\0"
    "state\0changeName\0updateCurve\0"
    "updateScreenSize\0width\0height\0"
    "getPointsIds\0changeBasis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiBezierCurveC2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,
       5,    2,   94,    2, 0x06 /* Public */,
       6,    1,   99,    2, 0x06 /* Public */,
       9,    1,  102,    2, 0x06 /* Public */,
      11,    2,  105,    2, 0x06 /* Public */,
      16,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    2,  113,    2, 0x0a /* Public */,
      20,    2,  118,    2, 0x0a /* Public */,
      23,    2,  123,    2, 0x0a /* Public */,
      25,    1,  128,    2, 0x08 /* Private */,
      27,    2,  131,    2, 0x08 /* Private */,
      28,    0,  136,    2, 0x08 /* Private */,
      29,    2,  137,    2, 0x08 /* Private */,
      32,    1,  142,    2, 0x08 /* Private */,
      33,    1,  145,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,
    QMetaType::Void, 0x80000000 | 14,   17,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 19, QMetaType::Int,    8,   10,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int,   22,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   10,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   30,   31,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   26,

       0        // eod
};

void UiBezierCurveC2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiBezierCurveC2 *_t = static_cast<UiBezierCurveC2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pointAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->nameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->requestedPoints((*reinterpret_cast< const QList<std::shared_ptr<Point3D> >(*)>(_a[1]))); break;
        case 3: _t->curveDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->addedControlPoints((*reinterpret_cast< std::vector<std::shared_ptr<Point3D> >(*)>(_a[1])),(*reinterpret_cast< const std::vector<int>(*)>(_a[2]))); break;
        case 5: _t->bezierCurve2Destroyed((*reinterpret_cast< const std::vector<int>(*)>(_a[1]))); break;
        case 6: _t->assignPoints((*reinterpret_cast< const std::vector<std::shared_ptr<DrawableObject> >(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->addPoint((*reinterpret_cast< const std::shared_ptr<DrawableObject>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->removePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->changePolylineState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changeName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->updateCurve(); break;
        case 12: _t->updateScreenSize((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 13: _t->getPointsIds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->changeBasis((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UiBezierCurveC2::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::pointAdded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC2::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::nameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC2::*_t)(const QList<std::shared_ptr<Point3D>> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::requestedPoints)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC2::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::curveDeleted)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC2::*_t)(std::vector<std::shared_ptr<Point3D>> , const std::vector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::addedControlPoints)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (UiBezierCurveC2::*_t)(const std::vector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiBezierCurveC2::bezierCurve2Destroyed)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject UiBezierCurveC2::staticMetaObject = {
    { &UiConnector::staticMetaObject, qt_meta_stringdata_UiBezierCurveC2.data,
      qt_meta_data_UiBezierCurveC2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UiBezierCurveC2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiBezierCurveC2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UiBezierCurveC2.stringdata0))
        return static_cast<void*>(const_cast< UiBezierCurveC2*>(this));
    return UiConnector::qt_metacast(_clname);
}

int UiBezierCurveC2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UiConnector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void UiBezierCurveC2::pointAdded(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UiBezierCurveC2::nameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiBezierCurveC2::requestedPoints(const QList<std::shared_ptr<Point3D>> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UiBezierCurveC2::curveDeleted(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UiBezierCurveC2::addedControlPoints(std::vector<std::shared_ptr<Point3D>> _t1, const std::vector<int> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UiBezierCurveC2::bezierCurve2Destroyed(const std::vector<int> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
