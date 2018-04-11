/****************************************************************************
** Meta object code from reading C++ file 'listWidgetParameters.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../listWidgetParameters.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listWidgetParameters.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ListWidgetParameters_t {
    QByteArrayData data[16];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidgetParameters_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidgetParameters_t qt_meta_stringdata_ListWidgetParameters = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ListWidgetParameters"
QT_MOC_LITERAL(1, 21, 10), // "rightClick"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "pos"
QT_MOC_LITERAL(4, 37, 11), // "removedItem"
QT_MOC_LITERAL(5, 49, 7), // "pointId"
QT_MOC_LITERAL(6, 57, 7), // "curveId"
QT_MOC_LITERAL(7, 65, 13), // "displayPoints"
QT_MOC_LITERAL(8, 79, 32), // "QList<std::shared_ptr<Point3D> >"
QT_MOC_LITERAL(9, 112, 6), // "points"
QT_MOC_LITERAL(10, 119, 15), // "pointAddedToBC0"
QT_MOC_LITERAL(11, 135, 2), // "id"
QT_MOC_LITERAL(12, 138, 19), // "pointRemovedFromBC0"
QT_MOC_LITERAL(13, 158, 15), // "updatePointName"
QT_MOC_LITERAL(14, 174, 4), // "name"
QT_MOC_LITERAL(15, 179, 13) // "updateCurveId"

    },
    "ListWidgetParameters\0rightClick\0\0pos\0"
    "removedItem\0pointId\0curveId\0displayPoints\0"
    "QList<std::shared_ptr<Point3D> >\0"
    "points\0pointAddedToBC0\0id\0pointRemovedFromBC0\0"
    "updatePointName\0name\0updateCurveId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidgetParameters[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   57,    2, 0x0a /* Public */,
      10,    1,   60,    2, 0x0a /* Public */,
      12,    1,   63,    2, 0x0a /* Public */,
      13,    2,   66,    2, 0x0a /* Public */,
      15,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   14,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void ListWidgetParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidgetParameters *_t = static_cast<ListWidgetParameters *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rightClick((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->removedItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->displayPoints((*reinterpret_cast< const QList<std::shared_ptr<Point3D> >(*)>(_a[1]))); break;
        case 3: _t->pointAddedToBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->pointRemovedFromBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updatePointName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->updateCurveId((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListWidgetParameters::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetParameters::rightClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ListWidgetParameters::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetParameters::removedItem)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ListWidgetParameters::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ListWidgetParameters.data,
      qt_meta_data_ListWidgetParameters,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWidgetParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidgetParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidgetParameters.stringdata0))
        return static_cast<void*>(const_cast< ListWidgetParameters*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ListWidgetParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ListWidgetParameters::rightClick(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ListWidgetParameters::removedItem(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
