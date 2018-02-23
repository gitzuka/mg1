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
#include <comboboxBezierCurveC0.h>
#include <comboboxTorus.h>
#include <listwidgetobjects.h>
#include <listwidgetparameters.h>
#include <myglwidget.h>

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
    ListWidgetObjects *listWidget_ObjectsList;
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
    QVBoxLayout *verticalLayout_10;
    ComboBoxBezierCurveC0 *comboBox_BezierCurveC0;
    ListWidgetParameters *listWidget_Parameters;
    QWidget *tab_Other;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButton_stereo;
    QLabel *label_stereoscopy_slider;
    QDoubleSpinBox *doubleSpinBox_e;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *checkBox_pointer;
    QLabel *label_screenCoords;
    QLabel *label_3dCoords;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ModelowanieGeometryczne1Class)
    {
        if (ModelowanieGeometryczne1Class->objectName().isEmpty())
            ModelowanieGeometryczne1Class->setObjectName(QStringLiteral("ModelowanieGeometryczne1Class"));
        ModelowanieGeometryczne1Class->resize(1107, 717);
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
        myTabWidget = new QTabWidget(centralWidget);
        myTabWidget->setObjectName(QStringLiteral("myTabWidget"));
        tab_Objects = new QWidget();
        tab_Objects->setObjectName(QStringLiteral("tab_Objects"));
        verticalLayout_4 = new QVBoxLayout(tab_Objects);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        listWidget_ObjectsList = new ListWidgetObjects(tab_Objects);
        listWidget_ObjectsList->setObjectName(QStringLiteral("listWidget_ObjectsList"));
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
        page_Torus->setGeometry(QRect(0, 0, 293, 505));
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
        page_BezierCurveC0->setGeometry(QRect(0, 0, 293, 505));
        verticalLayout_11 = new QVBoxLayout(page_BezierCurveC0);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(5);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        comboBox_BezierCurveC0 = new ComboBoxBezierCurveC0(page_BezierCurveC0);
        comboBox_BezierCurveC0->setObjectName(QStringLiteral("comboBox_BezierCurveC0"));

        verticalLayout_10->addWidget(comboBox_BezierCurveC0);

        listWidget_Parameters = new ListWidgetParameters(page_BezierCurveC0);
        listWidget_Parameters->setObjectName(QStringLiteral("listWidget_Parameters"));

        verticalLayout_10->addWidget(listWidget_Parameters);


        verticalLayout_11->addLayout(verticalLayout_10);

        toolBox->addItem(page_BezierCurveC0, QStringLiteral("Bezier Curve C0"));

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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        verticalLayout_6->addLayout(verticalLayout_5);

        myTabWidget->addTab(tab_Other, QString());

        verticalLayout->addWidget(myTabWidget);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(5);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(5, 0, -1, 0);
        checkBox_pointer = new QCheckBox(centralWidget);
        checkBox_pointer->setObjectName(QStringLiteral("checkBox_pointer"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_pointer->sizePolicy().hasHeightForWidth());
        checkBox_pointer->setSizePolicy(sizePolicy);
        checkBox_pointer->setMinimumSize(QSize(0, 20));
        checkBox_pointer->setMaximumSize(QSize(16777215, 10));
        checkBox_pointer->setIconSize(QSize(20, 20));
        checkBox_pointer->setTristate(false);

        verticalLayout_9->addWidget(checkBox_pointer, 0, Qt::AlignVCenter);

        label_screenCoords = new QLabel(centralWidget);
        label_screenCoords->setObjectName(QStringLiteral("label_screenCoords"));

        verticalLayout_9->addWidget(label_screenCoords);

        label_3dCoords = new QLabel(centralWidget);
        label_3dCoords->setObjectName(QStringLiteral("label_3dCoords"));
        label_3dCoords->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_9->addWidget(label_3dCoords);


        verticalLayout->addLayout(verticalLayout_9);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 2, 1);

        ModelowanieGeometryczne1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModelowanieGeometryczne1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1107, 26));
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
        toolBox->setCurrentIndex(1);
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
        myTabWidget->setTabText(myTabWidget->indexOf(tab_Parameters), QApplication::translate("ModelowanieGeometryczne1Class", "Parameters", Q_NULLPTR));
        radioButton_stereo->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Stereoscopy on/off", Q_NULLPTR));
        label_stereoscopy_slider->setText(QApplication::translate("ModelowanieGeometryczne1Class", "Stereoscopy e parameter:", Q_NULLPTR));
        myTabWidget->setTabText(myTabWidget->indexOf(tab_Other), QApplication::translate("ModelowanieGeometryczne1Class", "Other features", Q_NULLPTR));
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
