/****************************************************************************
** Meta object code from reading C++ file 'comboboxTorus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../comboboxTorus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comboboxTorus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComboBoxTorus_t {
    QByteArrayData data[17];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComboBoxTorus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComboBoxTorus_t qt_meta_stringdata_ComboBoxTorus = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ComboBoxTorus"
QT_MOC_LITERAL(1, 14, 13), // "smallrChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "r"
QT_MOC_LITERAL(4, 31, 8), // "objectId"
QT_MOC_LITERAL(5, 40, 11), // "bigRChanged"
QT_MOC_LITERAL(6, 52, 1), // "R"
QT_MOC_LITERAL(7, 54, 20), // "minorSegmentsChanged"
QT_MOC_LITERAL(8, 75, 8), // "segments"
QT_MOC_LITERAL(9, 84, 20), // "majorSegmentsChanged"
QT_MOC_LITERAL(10, 105, 14), // "changeItemText"
QT_MOC_LITERAL(11, 120, 4), // "text"
QT_MOC_LITERAL(12, 125, 10), // "deleteItem"
QT_MOC_LITERAL(13, 136, 12), // "changeSmallr"
QT_MOC_LITERAL(14, 149, 10), // "changeBigR"
QT_MOC_LITERAL(15, 160, 19), // "changeMinorSegments"
QT_MOC_LITERAL(16, 180, 19) // "changeMajorSegments"

    },
    "ComboBoxTorus\0smallrChanged\0\0r\0objectId\0"
    "bigRChanged\0R\0minorSegmentsChanged\0"
    "segments\0majorSegmentsChanged\0"
    "changeItemText\0text\0deleteItem\0"
    "changeSmallr\0changeBigR\0changeMinorSegments\0"
    "changeMajorSegments"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComboBoxTorus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    2,   69,    2, 0x06 /* Public */,
       7,    2,   74,    2, 0x06 /* Public */,
       9,    2,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   84,    2, 0x0a /* Public */,
      12,    1,   89,    2, 0x0a /* Public */,
      13,    1,   92,    2, 0x0a /* Public */,
      14,    1,   95,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,    6,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,   11,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void ComboBoxTorus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComboBoxTorus *_t = static_cast<ComboBoxTorus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->smallrChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->bigRChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->minorSegmentsChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->majorSegmentsChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->changeItemText((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->deleteItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->changeSmallr((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->changeBigR((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->changeMinorSegments((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeMajorSegments((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ComboBoxTorus::*_t)(double , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxTorus::smallrChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ComboBoxTorus::*_t)(double , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxTorus::bigRChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ComboBoxTorus::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxTorus::minorSegmentsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ComboBoxTorus::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComboBoxTorus::majorSegmentsChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ComboBoxTorus::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ComboBoxTorus.data,
      qt_meta_data_ComboBoxTorus,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ComboBoxTorus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComboBoxTorus::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ComboBoxTorus.stringdata0))
        return static_cast<void*>(const_cast< ComboBoxTorus*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ComboBoxTorus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ComboBoxTorus::smallrChanged(double _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComboBoxTorus::bigRChanged(double _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ComboBoxTorus::minorSegmentsChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ComboBoxTorus::majorSegmentsChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
