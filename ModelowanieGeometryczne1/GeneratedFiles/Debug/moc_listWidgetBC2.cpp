/****************************************************************************
** Meta object code from reading C++ file 'listWidgetBC2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../listWidgetBC2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listWidgetBC2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ListWidgetBC2_t {
    QByteArrayData data[17];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidgetBC2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidgetBC2_t qt_meta_stringdata_ListWidgetBC2 = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ListWidgetBC2"
QT_MOC_LITERAL(1, 14, 10), // "rightClick"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "pos"
QT_MOC_LITERAL(4, 30, 11), // "removedItem"
QT_MOC_LITERAL(5, 42, 7), // "pointId"
QT_MOC_LITERAL(6, 50, 7), // "curveId"
QT_MOC_LITERAL(7, 58, 13), // "displayPoints"
QT_MOC_LITERAL(8, 72, 32), // "QList<std::shared_ptr<Point3D> >"
QT_MOC_LITERAL(9, 105, 6), // "points"
QT_MOC_LITERAL(10, 112, 15), // "pointAddedToBC2"
QT_MOC_LITERAL(11, 128, 2), // "id"
QT_MOC_LITERAL(12, 131, 4), // "name"
QT_MOC_LITERAL(13, 136, 15), // "updatePointName"
QT_MOC_LITERAL(14, 152, 13), // "updateCurveId"
QT_MOC_LITERAL(15, 166, 13), // "highlightItem"
QT_MOC_LITERAL(16, 180, 8) // "objectId"

    },
    "ListWidgetBC2\0rightClick\0\0pos\0removedItem\0"
    "pointId\0curveId\0displayPoints\0"
    "QList<std::shared_ptr<Point3D> >\0"
    "points\0pointAddedToBC2\0id\0name\0"
    "updatePointName\0updateCurveId\0"
    "highlightItem\0objectId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidgetBC2[] = {

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
      10,    2,   60,    2, 0x0a /* Public */,
      13,    2,   65,    2, 0x0a /* Public */,
      14,    1,   70,    2, 0x0a /* Public */,
      15,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void ListWidgetBC2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidgetBC2 *_t = static_cast<ListWidgetBC2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rightClick((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->removedItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->displayPoints((*reinterpret_cast< const QList<std::shared_ptr<Point3D> >(*)>(_a[1]))); break;
        case 3: _t->pointAddedToBC2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->updatePointName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->updateCurveId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->highlightItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListWidgetBC2::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetBC2::rightClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ListWidgetBC2::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetBC2::removedItem)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ListWidgetBC2::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ListWidgetBC2.data,
      qt_meta_data_ListWidgetBC2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWidgetBC2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidgetBC2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidgetBC2.stringdata0))
        return static_cast<void*>(const_cast< ListWidgetBC2*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ListWidgetBC2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ListWidgetBC2::rightClick(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ListWidgetBC2::removedItem(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
