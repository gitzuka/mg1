/****************************************************************************
** Meta object code from reading C++ file 'comboBoxBezierCurveC0.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../comboBoxBezierCurveC0.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comboBoxBezierCurveC0.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComboBoxBezierCurveC0_t {
    QByteArrayData data[11];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComboBoxBezierCurveC0_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComboBoxBezierCurveC0_t qt_meta_stringdata_ComboBoxBezierCurveC0 = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ComboBoxBezierCurveC0"
QT_MOC_LITERAL(1, 22, 12), // "itemSelected"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "curveId"
QT_MOC_LITERAL(4, 44, 11), // "itemRemoved"
QT_MOC_LITERAL(5, 56, 14), // "changeItemText"
QT_MOC_LITERAL(6, 71, 8), // "objectId"
QT_MOC_LITERAL(7, 80, 4), // "text"
QT_MOC_LITERAL(8, 85, 10), // "deleteItem"
QT_MOC_LITERAL(9, 96, 11), // "selectCurve"
QT_MOC_LITERAL(10, 108, 6) // "itemId"

    },
    "ComboBoxBezierCurveC0\0itemSelected\0\0"
    "curveId\0itemRemoved\0changeItemText\0"
    "objectId\0text\0deleteItem\0selectCurve\0"
    "itemId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComboBoxBezierCurveC0[] = {

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
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   43,    2, 0x0a /* Public */,
       8,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void ComboBoxBezierCurveC0::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComboBoxBezierCurveC0 *_t = static_cast<ComboBoxBezierCurveC0 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->itemRemoved(); break;
        case 2: _t->changeItemText((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->deleteItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->selectCurve((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ComboBoxBezierCurveC0::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxBezierCurveC0::itemSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ComboBoxBezierCurveC0::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxBezierCurveC0::itemRemoved)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ComboBoxBezierCurveC0::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ComboBoxBezierCurveC0.data,
      qt_meta_data_ComboBoxBezierCurveC0,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ComboBoxBezierCurveC0::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComboBoxBezierCurveC0::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ComboBoxBezierCurveC0.stringdata0))
        return static_cast<void*>(const_cast< ComboBoxBezierCurveC0*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ComboBoxBezierCurveC0::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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
void ComboBoxBezierCurveC0::itemSelected(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComboBoxBezierCurveC0::itemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
