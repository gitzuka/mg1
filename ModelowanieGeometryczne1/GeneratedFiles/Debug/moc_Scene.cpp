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
    QByteArrayData data[78];
    char stringdata0[1164];
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
QT_MOC_LITERAL(13, 155, 25), // "addedBezierC2Interpolated"
QT_MOC_LITERAL(14, 181, 29), // "const UiBezierC2Interpolated*"
QT_MOC_LITERAL(15, 211, 20), // "addedBezierSurfaceC0"
QT_MOC_LITERAL(16, 232, 18), // "UiBezierSurfaceC0*"
QT_MOC_LITERAL(17, 251, 17), // "uiBezierSurfaceC0"
QT_MOC_LITERAL(18, 269, 20), // "addedBezierSurfaceC2"
QT_MOC_LITERAL(19, 290, 18), // "UiBezierSurfaceC2*"
QT_MOC_LITERAL(20, 309, 17), // "uiBezierSurfaceC2"
QT_MOC_LITERAL(21, 327, 12), // "addedPoint3D"
QT_MOC_LITERAL(22, 340, 16), // "const UiPoint3D*"
QT_MOC_LITERAL(23, 357, 6), // "object"
QT_MOC_LITERAL(24, 364, 18), // "addedTrimmingCurve"
QT_MOC_LITERAL(25, 383, 22), // "const UiTrimmingCurve*"
QT_MOC_LITERAL(26, 406, 13), // "trimmingCurve"
QT_MOC_LITERAL(27, 420, 6), // "update"
QT_MOC_LITERAL(28, 427, 11), // "editModeBC0"
QT_MOC_LITERAL(29, 439, 11), // "editModeBC2"
QT_MOC_LITERAL(30, 451, 14), // "editModeBC2Int"
QT_MOC_LITERAL(31, 466, 15), // "objectActivated"
QT_MOC_LITERAL(32, 482, 17), // "objectDeactivated"
QT_MOC_LITERAL(33, 500, 21), // "createdBSControlPoint"
QT_MOC_LITERAL(34, 522, 20), // "intersectionNotFound"
QT_MOC_LITERAL(35, 543, 17), // "intersectionFound"
QT_MOC_LITERAL(36, 561, 22), // "std::vector<QVector4D>"
QT_MOC_LITERAL(37, 584, 15), // "parametrization"
QT_MOC_LITERAL(38, 600, 8), // "uvRange1"
QT_MOC_LITERAL(39, 609, 8), // "uvRange2"
QT_MOC_LITERAL(40, 618, 31), // "std::shared_ptr<DrawableObject>"
QT_MOC_LITERAL(41, 650, 8), // "surface1"
QT_MOC_LITERAL(42, 659, 8), // "surface2"
QT_MOC_LITERAL(43, 668, 16), // "QPair<bool,bool>"
QT_MOC_LITERAL(44, 685, 6), // "s1Wrap"
QT_MOC_LITERAL(45, 692, 6), // "s2Wrap"
QT_MOC_LITERAL(46, 699, 19), // "updateControlPoints"
QT_MOC_LITERAL(47, 719, 38), // "std::vector<std::shared_ptr<P..."
QT_MOC_LITERAL(48, 758, 13), // "controlPoints"
QT_MOC_LITERAL(49, 772, 16), // "std::vector<int>"
QT_MOC_LITERAL(50, 789, 7), // "prevIds"
QT_MOC_LITERAL(51, 797, 18), // "removeUiConnectors"
QT_MOC_LITERAL(52, 816, 3), // "ids"
QT_MOC_LITERAL(53, 820, 19), // "performCursorAction"
QT_MOC_LITERAL(54, 840, 8), // "multiple"
QT_MOC_LITERAL(55, 849, 11), // "resetCursor"
QT_MOC_LITERAL(56, 861, 16), // "createObjectMenu"
QT_MOC_LITERAL(57, 878, 3), // "pos"
QT_MOC_LITERAL(58, 882, 10), // "QList<int>"
QT_MOC_LITERAL(59, 893, 12), // "deleteObject"
QT_MOC_LITERAL(60, 906, 19), // "selectCursorObjects"
QT_MOC_LITERAL(61, 926, 11), // "QList<int>&"
QT_MOC_LITERAL(62, 938, 9), // "loadScene"
QT_MOC_LITERAL(63, 948, 11), // "fileContent"
QT_MOC_LITERAL(64, 960, 9), // "saveScene"
QT_MOC_LITERAL(65, 970, 4), // "path"
QT_MOC_LITERAL(66, 975, 17), // "newtonStepChanged"
QT_MOC_LITERAL(67, 993, 3), // "val"
QT_MOC_LITERAL(68, 997, 27), // "selfIntersectionDistChanged"
QT_MOC_LITERAL(69, 1025, 21), // "newtonWrapDistChanged"
QT_MOC_LITERAL(70, 1047, 19), // "gradientStepChanged"
QT_MOC_LITERAL(71, 1067, 23), // "closestPointStepChanged"
QT_MOC_LITERAL(72, 1091, 21), // "newtonWrapIterChanged"
QT_MOC_LITERAL(73, 1113, 16), // "translateObjects"
QT_MOC_LITERAL(74, 1130, 16), // "findClosestPoint"
QT_MOC_LITERAL(75, 1147, 5), // "width"
QT_MOC_LITERAL(76, 1153, 6), // "height"
QT_MOC_LITERAL(77, 1160, 3) // "add"

    },
    "Scene\0addedTorus\0\0name\0id\0const UiTorus*\0"
    "uiTorus\0addedBezierCurveC0\0"
    "const UiBezierCurveC0*\0uiBezierC0\0"
    "addedBezierCurveC2\0const UiBezierCurveC2*\0"
    "uiBezierC2\0addedBezierC2Interpolated\0"
    "const UiBezierC2Interpolated*\0"
    "addedBezierSurfaceC0\0UiBezierSurfaceC0*\0"
    "uiBezierSurfaceC0\0addedBezierSurfaceC2\0"
    "UiBezierSurfaceC2*\0uiBezierSurfaceC2\0"
    "addedPoint3D\0const UiPoint3D*\0object\0"
    "addedTrimmingCurve\0const UiTrimmingCurve*\0"
    "trimmingCurve\0update\0editModeBC0\0"
    "editModeBC2\0editModeBC2Int\0objectActivated\0"
    "objectDeactivated\0createdBSControlPoint\0"
    "intersectionNotFound\0intersectionFound\0"
    "std::vector<QVector4D>\0parametrization\0"
    "uvRange1\0uvRange2\0std::shared_ptr<DrawableObject>\0"
    "surface1\0surface2\0QPair<bool,bool>\0"
    "s1Wrap\0s2Wrap\0updateControlPoints\0"
    "std::vector<std::shared_ptr<Point3D> >\0"
    "controlPoints\0std::vector<int>\0prevIds\0"
    "removeUiConnectors\0ids\0performCursorAction\0"
    "multiple\0resetCursor\0createObjectMenu\0"
    "pos\0QList<int>\0deleteObject\0"
    "selectCursorObjects\0QList<int>&\0"
    "loadScene\0fileContent\0saveScene\0path\0"
    "newtonStepChanged\0val\0selfIntersectionDistChanged\0"
    "newtonWrapDistChanged\0gradientStepChanged\0"
    "closestPointStepChanged\0newtonWrapIterChanged\0"
    "translateObjects\0findClosestPoint\0"
    "width\0height\0add"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  189,    2, 0x06 /* Public */,
       7,    3,  196,    2, 0x06 /* Public */,
      10,    3,  203,    2, 0x06 /* Public */,
      13,    3,  210,    2, 0x06 /* Public */,
      15,    3,  217,    2, 0x06 /* Public */,
      18,    3,  224,    2, 0x06 /* Public */,
      21,    3,  231,    2, 0x06 /* Public */,
      24,    3,  238,    2, 0x06 /* Public */,
      27,    0,  245,    2, 0x06 /* Public */,
      28,    1,  246,    2, 0x06 /* Public */,
      29,    1,  249,    2, 0x06 /* Public */,
      30,    1,  252,    2, 0x06 /* Public */,
      31,    1,  255,    2, 0x06 /* Public */,
      32,    1,  258,    2, 0x06 /* Public */,
      33,    3,  261,    2, 0x06 /* Public */,
      34,    0,  268,    2, 0x06 /* Public */,
      35,    7,  269,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      46,    2,  284,    2, 0x0a /* Public */,
      51,    1,  289,    2, 0x0a /* Public */,
      53,    1,  292,    2, 0x08 /* Private */,
      53,    0,  295,    2, 0x28 /* Private | MethodCloned */,
      55,    0,  296,    2, 0x08 /* Private */,
      56,    2,  297,    2, 0x08 /* Private */,
      59,    1,  302,    2, 0x08 /* Private */,
      60,    1,  305,    2, 0x08 /* Private */,
      62,    1,  308,    2, 0x08 /* Private */,
      64,    1,  311,    2, 0x08 /* Private */,
      66,    1,  314,    2, 0x08 /* Private */,
      68,    1,  317,    2, 0x08 /* Private */,
      69,    1,  320,    2, 0x08 /* Private */,
      70,    1,  323,    2, 0x08 /* Private */,
      71,    1,  326,    2, 0x08 /* Private */,
      72,    1,  329,    2, 0x08 /* Private */,
      73,    1,  332,    2, 0x08 /* Private */,
      74,    4,  335,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 8,    3,    4,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 11,    3,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 14,    3,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 16,    3,    4,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 19,    3,    4,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 22,    3,    4,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 25,    3,    4,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 22,    3,    4,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36, QMetaType::QVector4D, QMetaType::QVector4D, 0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 43, 0x80000000 | 43,   37,   38,   39,   41,   42,   44,   45,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 47, 0x80000000 | 49,   48,   50,
    QMetaType::Void, 0x80000000 | 49,   52,
    QMetaType::Void, QMetaType::Bool,   54,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 58,   57,   52,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 61,   52,
    QMetaType::Void, QMetaType::QString,   63,
    QMetaType::Void, QMetaType::QString,   65,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::QVector3D,   57,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   57,   75,   76,   77,

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
        case 3: _t->addedBezierC2Interpolated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiBezierC2Interpolated*(*)>(_a[3]))); break;
        case 4: _t->addedBezierSurfaceC0((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< UiBezierSurfaceC0*(*)>(_a[3]))); break;
        case 5: _t->addedBezierSurfaceC2((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< UiBezierSurfaceC2*(*)>(_a[3]))); break;
        case 6: _t->addedPoint3D((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiPoint3D*(*)>(_a[3]))); break;
        case 7: _t->addedTrimmingCurve((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiTrimmingCurve*(*)>(_a[3]))); break;
        case 8: _t->update(); break;
        case 9: _t->editModeBC0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->editModeBC2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->editModeBC2Int((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->objectActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->objectDeactivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->createdBSControlPoint((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const UiPoint3D*(*)>(_a[3]))); break;
        case 15: _t->intersectionNotFound(); break;
        case 16: _t->intersectionFound((*reinterpret_cast< const std::vector<QVector4D>(*)>(_a[1])),(*reinterpret_cast< const QVector4D(*)>(_a[2])),(*reinterpret_cast< const QVector4D(*)>(_a[3])),(*reinterpret_cast< std::shared_ptr<DrawableObject>(*)>(_a[4])),(*reinterpret_cast< std::shared_ptr<DrawableObject>(*)>(_a[5])),(*reinterpret_cast< QPair<bool,bool>(*)>(_a[6])),(*reinterpret_cast< QPair<bool,bool>(*)>(_a[7]))); break;
        case 17: _t->updateControlPoints((*reinterpret_cast< std::vector<std::shared_ptr<Point3D> >(*)>(_a[1])),(*reinterpret_cast< const std::vector<int>(*)>(_a[2]))); break;
        case 18: _t->removeUiConnectors((*reinterpret_cast< const std::vector<int>(*)>(_a[1]))); break;
        case 19: _t->performCursorAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->performCursorAction(); break;
        case 21: _t->resetCursor(); break;
        case 22: _t->createObjectMenu((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const QList<int>(*)>(_a[2]))); break;
        case 23: _t->deleteObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->selectCursorObjects((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 25: _t->loadScene((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->saveScene((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: _t->newtonStepChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->selfIntersectionDistChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->newtonWrapDistChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->gradientStepChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->closestPointStepChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 32: _t->newtonWrapIterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->translateObjects((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 34: _t->findClosestPoint((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 22:
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
            typedef void (Scene::*_t)(const QString & , int , const UiBezierC2Interpolated * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierC2Interpolated)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , UiBezierSurfaceC0 * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierSurfaceC0)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , UiBezierSurfaceC2 * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedBezierSurfaceC2)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiPoint3D * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedPoint3D)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiTrimmingCurve * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::addedTrimmingCurve)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Scene::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::update)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::editModeBC0)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::editModeBC2)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::editModeBC2Int)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::objectActivated)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::objectDeactivated)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const QString & , int , const UiPoint3D * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::createdBSControlPoint)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (Scene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::intersectionNotFound)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (Scene::*_t)(const std::vector<QVector4D> & , const QVector4D & , const QVector4D & , std::shared_ptr<DrawableObject> , std::shared_ptr<DrawableObject> , QPair<bool,bool> , QPair<bool,bool> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::intersectionFound)) {
                *result = 16;
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
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
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
void Scene::addedBezierC2Interpolated(const QString & _t1, int _t2, const UiBezierC2Interpolated * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Scene::addedBezierSurfaceC0(const QString & _t1, int _t2, UiBezierSurfaceC0 * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Scene::addedBezierSurfaceC2(const QString & _t1, int _t2, UiBezierSurfaceC2 * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Scene::addedPoint3D(const QString & _t1, int _t2, const UiPoint3D * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Scene::addedTrimmingCurve(const QString & _t1, int _t2, const UiTrimmingCurve * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Scene::update()const
{
    QMetaObject::activate(const_cast< Scene *>(this), &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void Scene::editModeBC0(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Scene::editModeBC2(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Scene::editModeBC2Int(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Scene::objectActivated(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Scene::objectDeactivated(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Scene::createdBSControlPoint(const QString & _t1, int _t2, const UiPoint3D * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Scene::intersectionNotFound()
{
    QMetaObject::activate(this, &staticMetaObject, 15, Q_NULLPTR);
}

// SIGNAL 16
void Scene::intersectionFound(const std::vector<QVector4D> & _t1, const QVector4D & _t2, const QVector4D & _t3, std::shared_ptr<DrawableObject> _t4, std::shared_ptr<DrawableObject> _t5, QPair<bool,bool> _t6, QPair<bool,bool> _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
