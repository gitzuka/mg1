/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[34];
    char stringdata0[455];
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
QT_MOC_LITERAL(5, 26, 14), // "const UiTorus*"
QT_MOC_LITERAL(6, 41, 7), // "uiTorus"
QT_MOC_LITERAL(7, 49, 18), // "addedBezierCurveC0"
QT_MOC_LITERAL(8, 68, 22), // "const UiBezierCurveC0*"
QT_MOC_LITERAL(9, 91, 10), // "uiBezierC0"
QT_MOC_LITERAL(10, 102, 18), // "addedBezierCurveC2"
QT_MOC_LITERAL(11, 121, 22), // "const UiBezierCurveC2*"
QT_MOC_LITERAL(12, 144, 10), // "uiBezierC2"
QT_MOC_LITERAL(13, 155, 12), // "addedPoint3D"
QT_MOC_LITERAL(14, 168, 16), // "const UiPoint3D*"
QT_MOC_LITERAL(15, 185, 6), // "object"
QT_MOC_LITERAL(16, 192, 6), // "update"
QT_MOC_LITERAL(17, 199, 11), // "editModeBC0"
QT_MOC_LITERAL(18, 211, 11), // "editModeBC2"
QT_MOC_LITERAL(19, 223, 15), // "objectActivated"
QT_MOC_LITERAL(20, 239, 17), // "objectDeactivated"
QT_MOC_LITERAL(21, 257, 16), // "createObjectMenu"
QT_MOC_LITERAL(22, 274, 3), // "pos"
QT_MOC_LITERAL(23, 278, 10), // "QList<int>"
QT_MOC_LITERAL(24, 289, 3), // "ids"
QT_MOC_LITERAL(25, 293, 12), // "deleteObject"
QT_MOC_LITERAL(26, 306, 19), // "updateControlPoints"
QT_MOC_LITERAL(27, 326, 38), // "std::vector<std::shared_ptr<P..."
QT_MOC_LITERAL(28, 365, 13), // "controlPoints"
QT_MOC_LITERAL(29, 379, 16), // "std::vector<int>"
QT_MOC_LITERAL(30, 396, 7), // "prevIds"
QT_MOC_LITERAL(31, 404, 18), // "removeUiConnectors"
QT_MOC_LITERAL(32, 423, 19), // "performCursorAction"
QT_MOC_LITERAL(33, 443, 11) // "resetCursor"

    },
    "Scene\0addedTorus\0\0name\0id\0const UiTorus*\0"
    "uiTorus\0addedBezierCurveC0\0"
    "const UiBezierCurveC0*\0uiBezierC0\0"
    "addedBezierCurveC2\0const UiBezierCurveC2*\0"
    "uiBezierC2\0addedPoint3D\0const UiPoint3D*\0"
    "object\0update\0editModeBC0\0editModeBC2\0"
    "objectActivated\0objectDeactivated\0"
    "createObjectMenu\0pos\0QList<int>\0ids\0"
    "deleteObject\0updateControlPoints\0"
    "std::vector<std::shared_ptr<Point3D> >\0"
    "controlPoints\0std::vector<int>\0prevIds\0"
    "removeUiConnectors\0performCursorAction\0"
    "resetCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   89,    2, 0x06 /* Public */,
       7,    3,   96,    2, 0x06 /* Public */,
      10,    3,  103,    2, 0x06 /* Public */,
      13,    3,  110,    2, 0x06 /* Public */,
      16,    0,  117,    2, 0x06 /* Public */,
      17,    1,  118,    2, 0x06 /* Public */,
      18,    1,  121,    2, 0x06 /* Public */,
      19,    1,  124,    2, 0x06 /* Public */,
      20,    1,  127,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  130,    2, 0x0a /* Public */,
      25,    1,  135,    2, 0x0a /* Public */,
      26,    2,  138,    2, 0x0a /* Public */,
      31,    1,  143,    2, 0x0a /* Public */,
      32,    0,  146,    2, 0x08 /* Private */,
      33,    0,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 8,    3,    4,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 11,    3,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 14,    3,    4,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 23,   22,   24,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 27, 0x80000000 | 29,   28,   30,
    QMetaType::Void, 0x80000000 | 29,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scene *_t = static_cast<Scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addedTorus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiTorus*(*)>(_a[3]))); break;
        case 1: _t->addedBezierCurveC0((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiBezierCurveC0*(*)>(_a[3]))); break;
        case 2: _t->addedBezierCurveC2((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiBezierCurveC2*(*)>(_a[3]))); break;
        case 3: _t->addedPoint3D((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiPoint3D*(*)>(_a[3]))); break;
        case 4: _t->update(); break;
        case 5: _t->editModeBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->editModeBC2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->objectActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->objectDeactivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->createObjectMenu((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const QList<int>(*)>(_a[2]))); break;
        case 10: _t->deleteObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateControlPoints((*reinterpret_cast< std::vector<std::shared_ptr<Point3D> >(*)>(_a[1])),(*reinterpret_cast< const std::vector<int>(*)>(_a[2]))); break;
        case 12: _t->removeUiConnectors((*reinterpret_cast< const std::vector<int>(*)>(_a[1]))); break;
        case 13: _t->performCursorAction(); break;
        case 14: _t->resetCursor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
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
            typedef void (Scene::*_t)(const QString & , int , const UiTorus * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedTorus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiBezierCurveC0 * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierCurveC0)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiBezierCurveC2 * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierCurveC2)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiPoint3D * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedPoint3D)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Scene::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::update)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::editModeBC0)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::editModeBC2)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::objectActivated)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::objectDeactivated)) {
                *result = 8;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Scene::addedTorus(const QString & _t1, int _t2, const UiTorus * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Scene::addedBezierCurveC0(const QString & _t1, int _t2, const UiBezierCurveC0 * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Scene::addedBezierCurveC2(const QString & _t1, int _t2, const UiBezierCurveC2 * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Scene::addedPoint3D(const QString & _t1, int _t2, const UiPoint3D * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Scene::update()const
{
    QMetaObject::activate(const_cast< Scene *>(this), &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Scene::editModeBC0(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Scene::editModeBC2(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Scene::objectActivated(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Scene::objectDeactivated(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
