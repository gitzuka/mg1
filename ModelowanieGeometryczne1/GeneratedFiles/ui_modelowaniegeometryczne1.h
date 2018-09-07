/********************************************************************************
** Form generated from reading UI file 'modelowaniegeometryczne1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELOWANIEGEOMETRYCZNE1_H
#define UI_MODELOWANIEGEOMETRYCZNE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <comboBoxBezierCurveC0.h>
#include <comboBoxBezierSurface.h>
#include <comboBoxTorus.h>
#include <listWidgetBC0.h>
#include <listWidgetBC2.h>
#include <listWidgetBezierSurface.h>
#include <listWidgetMain.h>
#include <myGLWidget.h>

QT_BEGIN_NAMESPACE

class Ui_ModelowanieGeometryczne1Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    MyGLWidget *myGLWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *myTabWidget;
    QWidget *tab_Objects;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_15;
    ListWidgetMain *listWidget_ObjectsList;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_AddObject;
    QPushButton *pushButton_DeleteObject;
    QComboBox *comboBox_DrawableObjects;
    QWidget *tab_Parameters;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QToolBox *toolBox;
    QWidget *page_Torus;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    ComboBoxTorus *comboBox_Torus;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_smallR;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_bigR;
    QLabel *label;
    QSpinBox *spinBox_minorSegments;
    QLabel *label_2;
    QSpinBox *spinBox_majorSegments;
    QSpacerItem *verticalSpacer;
    QWidget *page_BezierCurveC0;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_BC0;
    ComboBoxBezierCurveC0 *comboBox_BezierCurveC0;
    ListWidgetBC0 *listWidget_BC0Parameters;
    QWidget *page_BezierCurveC2;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_BC2;
    ComboBoxBezierCurveC0 *comboBox_BC2;
    ListWidgetBC2 *listWidget_BC2;
    QWidget *page_BezierC2Int;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_BC2Int;
    ComboBoxBezierCurveC0 *comboBox_BC2Int;
    ListWidgetBC0 *listWidget_BC2Int;
    QWidget *page_bezierSurfaceC0;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_BSC0;
    ComboBoxBezierSurface *comboBox_BSC0;
    ListWidgetBezierSurface *listWidget_BSC0;
    QPushButton *pushButton_BSC0;
    QWidget *page_bezierSurfaceC2;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_BSC2;
    ComboBoxBezierSurface *comboBox_BSC2;
    ListWidgetBezierSurface *listWidget_BSC2;
    QPushButton *pushButton_BSC2;
    QWidget *tab_Other;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButton_stereo;
    QLabel *label_stereoscopy_slider;
    QDoubleSpinBox *doubleSpinBox_e;
    QLabel *label_5;
    QRadioButton *radioButton_Idle;
    QRadioButton *radioButton_Translate;
    QRadioButton *radioButton_Add;
    QRadioButton *radioButton_Delete;
    QPushButton *pushButton_Intersections;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_16;
    QGridLayout *gridLayout_ObjectDetails;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_RotY;
    QDoubleSpinBox *doubleSpinBox_PosX;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_PosZ;
    QDoubleSpinBox *doubleSpinBox_RotX;
    QLabel *label_11;
    QLabel *label_6;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_PosY;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_RotZ;
    QLabel *label_12;
    QLabel *label_13;
    QCheckBox *checkBox_pointer;
    QLabel *label_screenCoords;
    QLabel *label_3dCoords;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *doubleSpinBox_CursorX;
    QDoubleSpinBox *doubleSpinBox_CursorY;
    QDoubleSpinBox *doubleSpinBox_CursorZ;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *ModelowanieGeometryczne1Class)
    {
        if (ModelowanieGeometryczne1Class->objectName().isEmpty())
            ModelowanieGeometryczne1Class->setObjectName(QStringLiteral("ModelowanieGeometryczne1Class"));
        ModelowanieGeometryczne1Class->resize(1143, 914);
        ModelowanieGeometryczne1Class->setMouseTracking(false);
        ModelowanieGeometryczne1Class->setFocusPolicy(Qt::ClickFocus);
        centralWidget = new QWidget(ModelowanieGeometryczne1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        myGLWidget = new MyGLWidget(centralWidget);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setMinimumSize(QSize(800, 600));
        myGLWidget->setMaximumSize(QSize(80000, 60000));
        myGLWidget->setMouseTracking(true);
        myGLWidget->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(myGLWidget, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        myTabWidget = new QTabWidget(centralWidget);
        myTabWidget->setObjectName(QStringLiteral("myTabWidget"));
        tab_Objects = new QWidget();
        tab_Objects->setObjectName(QStringLiteral("tab_Objects"));
        verticalLayout_4 = new QVBoxLayout(tab_Objects);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));

        verticalLayout_4->addLayout(verticalLayout_15);

        listWidget_ObjectsList = new ListWidgetMain(tab_Objects);
        listWidget_ObjectsList->setObjectName(QStringLiteral("listWidget_ObjectsList"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget_ObjectsList->sizePolicy().hasHeightForWidth());
        listWidget_ObjectsList->setSizePolicy(sizePolicy);
        listWidget_ObjectsList->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_4->addWidget(listWidget_ObjectsList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        pushButton_AddObject = new QPushButton(tab_Objects);
        pushButton_AddObject->setObjectName(QStringLiteral("pushButton_AddObject"));

        horizontalLayout_2->addWidget(pushButton_AddObject);

        pushButton_DeleteObject = new QPushButton(tab_Objects);
        pushButton_DeleteObject->setObjectName(QStringLiteral("pushButton_DeleteObject"));

        horizontalLayout_2->addWidget(pushButton_DeleteObject);


        verticalLayout_4->addLayout(horizontalLayout_2);

        comboBox_DrawableObjects = new QComboBox(tab_Objects);
        comboBox_DrawableObjects->setObjectName(QStringLiteral("comboBox_DrawableObjects"));
        comboBox_DrawableObjects->setModelColumn(0);

        verticalLayout_4->addWidget(comboBox_DrawableObjects);

        myTabWidget->addTab(tab_Objects, QString());
        tab_Parameters = new QWidget();
        tab_Parameters->setObjectName(QStringLiteral("tab_Parameters"));
        verticalLayout_3 = new QVBoxLayout(tab_Parameters);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolBox = new QToolBox(tab_Parameters);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page_Torus = new QWidget();
        page_Torus->setObjectName(QStringLiteral("page_Torus"));
        page_Torus->setGeometry(QRect(0, 0, 296, 471));
        verticalLayout_8 = new QVBoxLayout(page_Torus);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, -1, -1, -1);
        comboBox_Torus = new ComboBoxTorus(page_Torus);
        comboBox_Torus->setObjectName(QStringLiteral("comboBox_Torus"));

        verticalLayout_7->addWidget(comboBox_Torus);

        label_4 = new QLabel(page_Torus);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_7->addWidget(label_4);

        doubleSpinBox_smallR = new QDoubleSpinBox(page_Torus);
        doubleSpinBox_smallR->setObjectName(QStringLiteral("doubleSpinBox_smallR"));
        doubleSpinBox_smallR->setMinimum(0.05);
        doubleSpinBox_smallR->setMaximum(1);
        doubleSpinBox_smallR->setSingleStep(0.05);
        doubleSpinBox_smallR->setValue(0.1);

        verticalLayout_7->addWidget(doubleSpinBox_smallR);

        label_3 = new QLabel(page_Torus);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_7->addWidget(label_3);

        doubleSpinBox_bigR = new QDoubleSpinBox(page_Torus);
        doubleSpinBox_bigR->setObjectName(QStringLiteral("doubleSpinBox_bigR"));
        doubleSpinBox_bigR->setMaximum(4);
        doubleSpinBox_bigR->setSingleStep(0.25);
        doubleSpinBox_bigR->setValue(0.3);

        verticalLayout_7->addWidget(doubleSpinBox_bigR);

        label = new QLabel(page_Torus);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_7->addWidget(label);

        spinBox_minorSegments = new QSpinBox(page_Torus);
        spinBox_minorSegments->setObjectName(QStringLiteral("spinBox_minorSegments"));
        spinBox_minorSegments->setMinimum(1);
        spinBox_minorSegments->setMaximum(100);
        spinBox_minorSegments->setValue(30);

        verticalLayout_7->addWidget(spinBox_minorSegments);

        label_2 = new QLabel(page_Torus);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_7->addWidget(label_2);

        spinBox_majorSegments = new QSpinBox(page_Torus);
        spinBox_majorSegments->setObjectName(QStringLiteral("spinBox_majorSegments"));
        spinBox_majorSegments->setMinimum(1);
        spinBox_majorSegments->setMaximum(100);
        spinBox_majorSegments->setValue(30);

        verticalLayout_7->addWidget(spinBox_majorSegments);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);


        verticalLayout_8->addLayout(verticalLayout_7);

        toolBox->addItem(page_Torus, QStringLiteral("Torus"));
        page_BezierCurveC0 = new QWidget();
        page_BezierCurveC0->setObjectName(QStringLiteral("page_BezierCurveC0"));
        page_BezierCurveC0->setGeometry(QRect(0, 0, 91, 118));
        verticalLayout_11 = new QVBoxLayout(page_BezierCurveC0);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_BC0 = new QVBoxLayout();
        verticalLayout_BC0->setSpacing(5);
        verticalLayout_BC0->setObjectName(QStringLiteral("verticalLayout_BC0"));
        comboBox_BezierCurveC0 = new ComboBoxBezierCurveC0(page_BezierCurveC0);
        comboBox_BezierCurveC0->setObjectName(QStringLiteral("comboBox_BezierCurveC0"));

        verticalLayout_BC0->addWidget(comboBox_BezierCurveC0);

        listWidget_BC0Parameters = new ListWidgetBC0(page_BezierCurveC0);
        listWidget_BC0Parameters->setObjectName(QStringLiteral("listWidget_BC0Parameters"));
        listWidget_BC0Parameters->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_BC0->addWidget(listWidget_BC0Parameters);


        verticalLayout_11->addLayout(verticalLayout_BC0);

        toolBox->addItem(page_BezierCurveC0, QStringLiteral("Bezier Curve C0"));
        page_BezierCurveC2 = new QWidget();
        page_BezierCurveC2->setObjectName(QStringLiteral("page_BezierCurveC2"));
        page_BezierCurveC2->setGeometry(QRect(0, 0, 91, 118));
        verticalLayout_12 = new QVBoxLayout(page_BezierCurveC2);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_BC2 = new QVBoxLayout();
        verticalLayout_BC2->setSpacing(5);
        verticalLayout_BC2->setObjectName(QStringLiteral("verticalLayout_BC2"));
        comboBox_BC2 = new ComboBoxBezierCurveC0(page_BezierCurveC2);
        comboBox_BC2->setObjectName(QStringLiteral("comboBox_BC2"));

        verticalLayout_BC2->addWidget(comboBox_BC2);

        listWidget_BC2 = new ListWidgetBC2(page_BezierCurveC2);
        listWidget_BC2->setObjectName(QStringLiteral("listWidget_BC2"));

        verticalLayout_BC2->addWidget(listWidget_BC2);


        verticalLayout_12->addLayout(verticalLayout_BC2);

        toolBox->addItem(page_BezierCurveC2, QStringLiteral("Bezier Curve C2"));
        page_BezierC2Int = new QWidget();
        page_BezierC2Int->setObjectName(QStringLiteral("page_BezierC2Int"));
        page_BezierC2Int->setGeometry(QRect(0, 0, 91, 118));
        verticalLayout_10 = new QVBoxLayout(page_BezierC2Int);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_BC2Int = new QVBoxLayout();
        verticalLayout_BC2Int->setSpacing(5);
        verticalLayout_BC2Int->setObjectName(QStringLiteral("verticalLayout_BC2Int"));
        comboBox_BC2Int = new ComboBoxBezierCurveC0(page_BezierC2Int);
        comboBox_BC2Int->setObjectName(QStringLiteral("comboBox_BC2Int"));

        verticalLayout_BC2Int->addWidget(comboBox_BC2Int);

        listWidget_BC2Int = new ListWidgetBC0(page_BezierC2Int);
        listWidget_BC2Int->setObjectName(QStringLiteral("listWidget_BC2Int"));

        verticalLayout_BC2Int->addWidget(listWidget_BC2Int);


        verticalLayout_10->addLayout(verticalLayout_BC2Int);

        toolBox->addItem(page_BezierC2Int, QStringLiteral("Bezier Curve C2 Interpolated"));
        page_bezierSurfaceC0 = new QWidget();
        page_bezierSurfaceC0->setObjectName(QStringLiteral("page_bezierSurfaceC0"));
        page_bezierSurfaceC0->setGeometry(QRect(0, 0, 95, 151));
        verticalLayout_13 = new QVBoxLayout(page_bezierSurfaceC0);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_BSC0 = new QVBoxLayout();
        verticalLayout_BSC0->setSpacing(5);
        verticalLayout_BSC0->setObjectName(QStringLiteral("verticalLayout_BSC0"));
        comboBox_BSC0 = new ComboBoxBezierSurface(page_bezierSurfaceC0);
        comboBox_BSC0->setObjectName(QStringLiteral("comboBox_BSC0"));

        verticalLayout_BSC0->addWidget(comboBox_BSC0);

        listWidget_BSC0 = new ListWidgetBezierSurface(page_bezierSurfaceC0);
        listWidget_BSC0->setObjectName(QStringLiteral("listWidget_BSC0"));

        verticalLayout_BSC0->addWidget(listWidget_BSC0);

        pushButton_BSC0 = new QPushButton(page_bezierSurfaceC0);
        pushButton_BSC0->setObjectName(QStringLiteral("pushButton_BSC0"));

        verticalLayout_BSC0->addWidget(pushButton_BSC0);


        verticalLayout_13->addLayout(verticalLayout_BSC0);

        toolBox->addItem(page_bezierSurfaceC0, QStringLiteral("Bezier Surface C0"));
        page_bezierSurfaceC2 = new QWidget();
        page_bezierSurfaceC2->setObjectName(QStringLiteral("page_bezierSurfaceC2"));
        page_bezierSurfaceC2->setGeometry(QRect(0, 0, 95, 151));
        verticalLayout_14 = new QVBoxLayout(page_bezierSurfaceC2);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        verticalLayout_BSC2 = new QVBoxLayout();
        verticalLayout_BSC2->setSpacing(5);
        verticalLayout_BSC2->setObjectName(QStringLiteral("verticalLayout_BSC2"));
        comboBox_BSC2 = new ComboBoxBezierSurface(page_bezierSurfaceC2);
        comboBox_BSC2->setObjectName(QStringLiteral("comboBox_BSC2"));

        verticalLayout_BSC2->addWidget(comboBox_BSC2);

        listWidget_BSC2 = new ListWidgetBezierSurface(page_bezierSurfaceC2);
        listWidget_BSC2->setObjectName(QStringLiteral("listWidget_BSC2"));

        verticalLayout_BSC2->addWidget(listWidget_BSC2);

        pushButton_BSC2 = new QPushButton(page_bezierSurfaceC2);
        pushButton_BSC2->setObjectName(QStringLiteral("pushButton_BSC2"));

        verticalLayout_BSC2->addWidget(pushButton_BSC2);


        verticalLayout_14->addLayout(verticalLayout_BSC2);

        toolBox->addItem(page_bezierSurfaceC2, QStringLiteral("Bezier Surface C2"));

        verticalLayout_2->addWidget(toolBox);


        verticalLayout_3->addLayout(verticalLayout_2);

        myTabWidget->addTab(tab_Parameters, QString());
        tab_Other = new QWidget();
        tab_Other->setObjectName(QStringLiteral("tab_Other"));
        verticalLayout_6 = new QVBoxLayout(tab_Other);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, -1, -1, -1);
        radioButton_stereo = new QRadioButton(tab_Other);
        radioButton_stereo->setObjectName(QStringLiteral("radioButton_stereo"));

        verticalLayout_5->addWidget(radioButton_stereo);

        label_stereoscopy_slider = new QLabel(tab_Other);
        label_stereoscopy_slider->setObjectName(QStringLiteral("label_stereoscopy_slider"));

        verticalLayout_5->addWidget(label_stereoscopy_slider);

        doubleSpinBox_e = new QDoubleSpinBox(tab_Other);
        doubleSpinBox_e->setObjectName(QStringLiteral("doubleSpinBox_e"));
        doubleSpinBox_e->setMinimum(-1);
        doubleSpinBox_e->setMaximum(1);
        doubleSpinBox_e->setSingleStep(0.01);
        doubleSpinBox_e->setValue(0.1);

        verticalLayout_5->addWidget(doubleSpinBox_e);

        label_5 = new QLabel(tab_Other);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_5->addWidget(label_5);

        radioButton_Idle = new QRadioButton(tab_Other);
        buttonGroup = new QButtonGroup(ModelowanieGeometryczne1Class);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton_Idle);
        radioButton_Idle->setObjectName(QStringLiteral("radioButton_Idle"));

        verticalLayout_5->addWidget(radioButton_Idle);

        radioButton_Translate = new QRadioButton(tab_Other);
        buttonGroup->addButton(radioButton_Translate);
        radioButton_Translate->setObjectName(QStringLiteral("radioButton_Translate"));
        radioButton_Translate->setChecked(true);

        verticalLayout_5->addWidget(radioButton_Translate);

        radioButton_Add = new QRadioButton(tab_Other);
        buttonGroup->addButton(radioButton_Add);
        radioButton_Add->setObjectName(QStringLiteral("radioButton_Add"));

        verticalLayout_5->addWidget(radioButton_Add);

        radioButton_Delete = new QRadioButton(tab_Other);
        buttonGroup->addButton(radioButton_Delete);
        radioButton_Delete->setObjectName(QStringLiteral("radioButton_Delete"));

        verticalLayout_5->addWidget(radioButton_Delete);

        pushButton_Intersections = new QPushButton(tab_Other);
        pushButton_Intersections->setObjectName(QStringLiteral("pushButton_Intersections"));

        verticalLayout_5->addWidget(pushButton_Intersections);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        verticalLayout_6->addLayout(verticalLayout_5);

        myTabWidget->addTab(tab_Other, QString());

        verticalLayout->addWidget(myTabWidget);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(5);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(5, 0, -1, 0);
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_ObjectDetails = new QGridLayout();
        gridLayout_ObjectDetails->setSpacing(6);
        gridLayout_ObjectDetails->setObjectName(QStringLiteral("gridLayout_ObjectDetails"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_7, 3, 0, 1, 1);

        doubleSpinBox_RotY = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_RotY->setObjectName(QStringLiteral("doubleSpinBox_RotY"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(doubleSpinBox_RotY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_RotY->setSizePolicy(sizePolicy2);
        doubleSpinBox_RotY->setMaximum(360);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_RotY, 3, 3, 1, 1);

        doubleSpinBox_PosX = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_PosX->setObjectName(QStringLiteral("doubleSpinBox_PosX"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_PosX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_PosX->setSizePolicy(sizePolicy2);
        doubleSpinBox_PosX->setMinimum(-20);
        doubleSpinBox_PosX->setMaximum(20);
        doubleSpinBox_PosX->setSingleStep(0.01);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_PosX, 1, 1, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_8, 1, 4, 1, 1);

        doubleSpinBox_PosZ = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_PosZ->setObjectName(QStringLiteral("doubleSpinBox_PosZ"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_PosZ->sizePolicy().hasHeightForWidth());
        doubleSpinBox_PosZ->setSizePolicy(sizePolicy2);
        doubleSpinBox_PosZ->setMinimum(-20);
        doubleSpinBox_PosZ->setMaximum(20);
        doubleSpinBox_PosZ->setSingleStep(0.01);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_PosZ, 1, 5, 1, 1);

        doubleSpinBox_RotX = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_RotX->setObjectName(QStringLiteral("doubleSpinBox_RotX"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_RotX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_RotX->setSizePolicy(sizePolicy2);
        doubleSpinBox_RotX->setMaximum(360);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_RotX, 3, 1, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_11, 3, 2, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_6, 1, 0, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_10, 1, 2, 1, 1);

        doubleSpinBox_PosY = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_PosY->setObjectName(QStringLiteral("doubleSpinBox_PosY"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_PosY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_PosY->setSizePolicy(sizePolicy2);
        doubleSpinBox_PosY->setMinimum(-20);
        doubleSpinBox_PosY->setMaximum(20);
        doubleSpinBox_PosY->setSingleStep(0.01);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_PosY, 1, 3, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout_ObjectDetails->addWidget(label_9, 3, 4, 1, 1);

        doubleSpinBox_RotZ = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_RotZ->setObjectName(QStringLiteral("doubleSpinBox_RotZ"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_RotZ->sizePolicy().hasHeightForWidth());
        doubleSpinBox_RotZ->setSizePolicy(sizePolicy2);
        doubleSpinBox_RotZ->setMaximum(360);

        gridLayout_ObjectDetails->addWidget(doubleSpinBox_RotZ, 3, 5, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_ObjectDetails->addWidget(label_12, 0, 0, 1, 6);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_ObjectDetails->addWidget(label_13, 2, 0, 1, 6);


        verticalLayout_16->addLayout(gridLayout_ObjectDetails);


        verticalLayout_9->addLayout(verticalLayout_16);

        checkBox_pointer = new QCheckBox(centralWidget);
        checkBox_pointer->setObjectName(QStringLiteral("checkBox_pointer"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox_pointer->sizePolicy().hasHeightForWidth());
        checkBox_pointer->setSizePolicy(sizePolicy3);
        checkBox_pointer->setMinimumSize(QSize(0, 20));
        checkBox_pointer->setMaximumSize(QSize(16777215, 10));
        checkBox_pointer->setIconSize(QSize(20, 20));
        checkBox_pointer->setTristate(false);

        verticalLayout_9->addWidget(checkBox_pointer);

        label_screenCoords = new QLabel(centralWidget);
        label_screenCoords->setObjectName(QStringLiteral("label_screenCoords"));

        verticalLayout_9->addWidget(label_screenCoords);

        label_3dCoords = new QLabel(centralWidget);
        label_3dCoords->setObjectName(QStringLiteral("label_3dCoords"));
        label_3dCoords->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_9->addWidget(label_3dCoords);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        doubleSpinBox_CursorX = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_CursorX->setObjectName(QStringLiteral("doubleSpinBox_CursorX"));
        doubleSpinBox_CursorX->setDecimals(4);
        doubleSpinBox_CursorX->setMinimum(-20);
        doubleSpinBox_CursorX->setMaximum(20);
        doubleSpinBox_CursorX->setSingleStep(0.01);

        horizontalLayout_4->addWidget(doubleSpinBox_CursorX);

        doubleSpinBox_CursorY = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_CursorY->setObjectName(QStringLiteral("doubleSpinBox_CursorY"));
        doubleSpinBox_CursorY->setDecimals(4);
        doubleSpinBox_CursorY->setMinimum(-20);
        doubleSpinBox_CursorY->setMaximum(20);
        doubleSpinBox_CursorY->setSingleStep(0.01);

        horizontalLayout_4->addWidget(doubleSpinBox_CursorY);

        doubleSpinBox_CursorZ = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_CursorZ->setObjectName(QStringLiteral("doubleSpinBox_CursorZ"));
        doubleSpinBox_CursorZ->setDecimals(4);
        doubleSpinBox_CursorZ->setMinimum(-20);
        doubleSpinBox_CursorZ->setMaximum(20);
        doubleSpinBox_CursorZ->setSingleStep(0.01);

        horizontalLayout_4->addWidget(doubleSpinBox_CursorZ);


        verticalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_9);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 30);
        horizontalLayout->setStretch(1, 11);

        gridLayout_2->addLayout(horizontalLayout, 0, 0, 2, 1);

        ModelowanieGeometryczne1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModelowanieGeometryczne1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 26));
        menuBar->setDefaultUp(false);
        ModelowanieGeometryczne1Class->setMenuBar(menuBar);
        statusBar = new QStatusBar(ModelowanieGeometryczne1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ModelowanieGeometryczne1Class->setStatusBar(statusBar);
        mainToolBar = new QToolBar(ModelowanieGeometryczne1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ModelowanieGeometryczne1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(ModelowanieGeometryczne1Class);

        myTabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);
        toolBox->layout()->setSpacing(0);


        QMetaObject::connectSlotsByName(ModelowanieGeometryczne1Class);
    } // setupUi

    void retranslateUi(QMainWindow *ModelowanieGeometryczne1Class)
    {
        ModelowanieGeometryczne1Class->setWindowTitle(QApplication::translate("ModelowanieGeometryczne1Class", "ModelowanieGeometryczne1", Q_NULLPTR));
        pushButton_AddObject->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Add", Q_NULLPTR));
        pushButton_DeleteObject->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Delete", Q_NULLPTR));
        myTabWidget->setTabText(myTabWidget->indexOf(tab_Objects), QApplication::translate("ModelowanieGeometryczne1Class", "Objects", Q_NULLPTR));
        label_4->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Small radius", Q_NULLPTR));
        label_3->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Big radius", Q_NULLPTR));
        label->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Minor segments", Q_NULLPTR));
        label_2->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Major segments", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_Torus), QApplication::translate("ModelowanieGeometryczne1Class", "Torus", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_BezierCurveC0), QApplication::translate("ModelowanieGeometryczne1Class", "Bezier Curve C0", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_BezierCurveC2), QApplication::translate("ModelowanieGeometryczne1Class", "Bezier Curve C2", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_BezierC2Int), QApplication::translate("ModelowanieGeometryczne1Class", "Bezier Curve C2 Interpolated", Q_NULLPTR));
        pushButton_BSC0->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Edit surface", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_bezierSurfaceC0), QApplication::translate("ModelowanieGeometryczne1Class", "Bezier Surface C0", Q_NULLPTR));
        pushButton_BSC2->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Edit surface", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_bezierSurfaceC2), QApplication::translate("ModelowanieGeometryczne1Class", "Bezier Surface C2", Q_NULLPTR));
        myTabWidget->setTabText(myTabWidget->indexOf(tab_Parameters), QApplication::translate("ModelowanieGeometryczne1Class", "Parameters", Q_NULLPTR));
        radioButton_stereo->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Stereoscopy on/off", Q_NULLPTR));
        label_stereoscopy_slider->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Stereoscopy e parameter:", Q_NULLPTR));
        label_5->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Cursor mode:", Q_NULLPTR));
        radioButton_Idle->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Idle", Q_NULLPTR));
        radioButton_Translate->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Translate", Q_NULLPTR));
        radioButton_Add->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Add", Q_NULLPTR));
        radioButton_Delete->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Delete", Q_NULLPTR));
        pushButton_Intersections->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Find intersections", Q_NULLPTR));
        myTabWidget->setTabText(myTabWidget->indexOf(tab_Other), QApplication::translate("ModelowanieGeometryczne1Class", "Other features", Q_NULLPTR));
        label_7->setText(QApplication::translate("ModelowanieGeometryczne1Class", "X", Q_NULLPTR));
        label_8->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Z", Q_NULLPTR));
        label_11->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Y", Q_NULLPTR));
        label_6->setText(QApplication::translate("ModelowanieGeometryczne1Class", "X", Q_NULLPTR));
        label_10->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Y", Q_NULLPTR));
        label_9->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Z", Q_NULLPTR));
        label_12->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Position", Q_NULLPTR));
        label_13->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Rotation", Q_NULLPTR));
        checkBox_pointer->setText(QApplication::translate("ModelowanieGeometryczne1Class", "3d pointer", Q_NULLPTR));
        label_screenCoords->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Screen coords:", Q_NULLPTR));
        label_3dCoords->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Scene coords:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ModelowanieGeometryczne1Class: public Ui_ModelowanieGeometryczne1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELOWANIEGEOMETRYCZNE1_H
