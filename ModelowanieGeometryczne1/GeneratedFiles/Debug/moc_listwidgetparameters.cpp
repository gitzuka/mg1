/****************************************************************************
** Meta object code from reading C++ file 'listwidgetparameters.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../listwidgetparameters.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listwidgetparameters.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ListWidgetParameters_t {
    QByteArrayData data[10];
    char stringdata0[133];
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
QT_MOC_LITERAL(4, 37, 35), // "comboBox_BezierCurveC0Display..."
QT_MOC_LITERAL(5, 73, 15), // "pointAddedToBC0"
QT_MOC_LITERAL(6, 89, 2), // "id"
QT_MOC_LITERAL(7, 92, 19), // "pointRemovedFromBC0"
QT_MOC_LITERAL(8, 112, 15), // "updatePointName"
QT_MOC_LITERAL(9, 128, 4) // "name"

    },
    "ListWidgetParameters\0rightClick\0\0pos\0"
    "comboBox_BezierCurveC0DisplayPoints\0"
    "pointAddedToBC0\0id\0pointRemovedFromBC0\0"
    "updatePointName\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidgetParameters[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x0a /* Public */,
       5,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       8,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    9,    6,

       0        // eod
};

void ListWidgetParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidgetParameters *_t = static_cast<ListWidgetParameters *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rightClick((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->comboBox_BezierCurveC0DisplayPoints((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->pointAddedToBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->pointRemovedFromBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updatePointName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
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
void ListWidgetParameters::rightClick(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
