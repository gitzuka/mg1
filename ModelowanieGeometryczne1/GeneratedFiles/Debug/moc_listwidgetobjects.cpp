/****************************************************************************
** Meta object code from reading C++ file 'listWidgetObjects.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../listWidgetObjects.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listWidgetObjects.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ListWidgetObjects_t {
    QByteArrayData data[19];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidgetObjects_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidgetObjects_t qt_meta_stringdata_ListWidgetObjects = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ListWidgetObjects"
QT_MOC_LITERAL(1, 18, 10), // "rightClick"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "pos"
QT_MOC_LITERAL(4, 34, 10), // "QList<int>"
QT_MOC_LITERAL(5, 45, 17), // "selectedObjectIds"
QT_MOC_LITERAL(6, 63, 19), // "changeItemTextEvent"
QT_MOC_LITERAL(7, 83, 4), // "text"
QT_MOC_LITERAL(8, 88, 8), // "objectId"
QT_MOC_LITERAL(9, 97, 15), // "removeItemEvent"
QT_MOC_LITERAL(10, 113, 16), // "addBezierCurveC0"
QT_MOC_LITERAL(11, 130, 8), // "addTorus"
QT_MOC_LITERAL(12, 139, 10), // "addPoint3D"
QT_MOC_LITERAL(13, 150, 10), // "removeItem"
QT_MOC_LITERAL(14, 161, 13), // "highlightItem"
QT_MOC_LITERAL(15, 175, 15), // "itemTextChanged"
QT_MOC_LITERAL(16, 191, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 208, 4), // "item"
QT_MOC_LITERAL(18, 213, 9) // "itemClick"

    },
    "ListWidgetObjects\0rightClick\0\0pos\0"
    "QList<int>\0selectedObjectIds\0"
    "changeItemTextEvent\0text\0objectId\0"
    "removeItemEvent\0addBezierCurveC0\0"
    "addTorus\0addPoint3D\0removeItem\0"
    "highlightItem\0itemTextChanged\0"
    "QListWidgetItem*\0item\0itemClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidgetObjects[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       6,    2,   69,    2, 0x06 /* Public */,
       9,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   77,    2, 0x0a /* Public */,
      11,    2,   82,    2, 0x0a /* Public */,
      12,    2,   87,    2, 0x0a /* Public */,
      13,    0,   92,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x0a /* Public */,
      15,    1,   96,    2, 0x08 /* Private */,
      18,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void ListWidgetObjects::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidgetObjects *_t = static_cast<ListWidgetObjects *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rightClick((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const QList<int>(*)>(_a[2]))); break;
        case 1: _t->changeItemTextEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->removeItemEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addBezierCurveC0((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->addTorus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->addPoint3D((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->removeItem(); break;
        case 7: _t->highlightItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->itemTextChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->itemClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListWidgetObjects::*_t)(const QPoint & , const QList<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetObjects::rightClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ListWidgetObjects::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetObjects::changeItemTextEvent)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ListWidgetObjects::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidgetObjects::removeItemEvent)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ListWidgetObjects::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ListWidgetObjects.data,
      qt_meta_data_ListWidgetObjects,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWidgetObjects::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidgetObjects::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidgetObjects.stringdata0))
        return static_cast<void*>(const_cast< ListWidgetObjects*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ListWidgetObjects::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ListWidgetObjects::rightClick(const QPoint & _t1, const QList<int> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ListWidgetObjects::changeItemTextEvent(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ListWidgetObjects::removeItemEvent(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
