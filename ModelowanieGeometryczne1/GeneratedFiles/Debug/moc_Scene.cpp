/****************************************************************************
** Meta object code from reading C++ file 'Scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[17];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scene_t qt_meta_stringdata_Scene = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Scene"
QT_MOC_LITERAL(1, 6, 10), // "addedTorus"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "name"
QT_MOC_LITERAL(4, 23, 2), // "id"
QT_MOC_LITERAL(5, 26, 22), // "std::shared_ptr<Torus>"
QT_MOC_LITERAL(6, 49, 6), // "object"
QT_MOC_LITERAL(7, 56, 18), // "addedBezierCurveC0"
QT_MOC_LITERAL(8, 75, 30), // "std::shared_ptr<BezierCurveC0>"
QT_MOC_LITERAL(9, 106, 12), // "addedPoint3D"
QT_MOC_LITERAL(10, 119, 31), // "std::shared_ptr<DrawableObject>"
QT_MOC_LITERAL(11, 151, 6), // "update"
QT_MOC_LITERAL(12, 158, 16), // "createObjectMenu"
QT_MOC_LITERAL(13, 175, 3), // "pos"
QT_MOC_LITERAL(14, 179, 10), // "QList<int>"
QT_MOC_LITERAL(15, 190, 3), // "ids"
QT_MOC_LITERAL(16, 194, 13) // "removedObject"

    },
    "Scene\0addedTorus\0\0name\0id\0"
    "std::shared_ptr<Torus>\0object\0"
    "addedBezierCurveC0\0std::shared_ptr<BezierCurveC0>\0"
    "addedPoint3D\0std::shared_ptr<DrawableObject>\0"
    "update\0createObjectMenu\0pos\0QList<int>\0"
    "ids\0removedObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       7,    3,   51,    2, 0x06 /* Public */,
       9,    3,   58,    2, 0x06 /* Public */,
      11,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   66,    2, 0x0a /* Public */,
      16,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 8,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 10,    3,    4,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 14,   13,   15,
    QMetaType::Void,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scene *_t = static_cast<Scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addedTorus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<Torus>(*)>(_a[3]))); break;
        case 1: _t->addedBezierCurveC0((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<BezierCurveC0>(*)>(_a[3]))); break;
        case 2: _t->addedPoint3D((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<DrawableObject>(*)>(_a[3]))); break;
        case 3: _t->update(); break;
        case 4: _t->createObjectMenu((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const QList<int>(*)>(_a[2]))); break;
        case 5: _t->removedObject(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
            typedef void (Scene::*_t)(QString , int , const std::shared_ptr<Torus> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedTorus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(QString , int , const std::shared_ptr<BezierCurveC0> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierCurveC0)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(QString , int , const std::shared_ptr<DrawableObject> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedPoint3D)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Scene::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::update)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Scene::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Scene.data,
      qt_meta_data_Scene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Scene.stringdata0))
        return static_cast<void*>(const_cast< Scene*>(this));
    return QObject::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Scene::addedTorus(QString _t1, int _t2, const std::shared_ptr<Torus> & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Scene::addedBezierCurveC0(QString _t1, int _t2, const std::shared_ptr<BezierCurveC0> & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Scene::addedPoint3D(QString _t1, int _t2, const std::shared_ptr<DrawableObject> & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Scene::update()const
{
    QMetaObject::activate(const_cast< Scene *>(this), &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
