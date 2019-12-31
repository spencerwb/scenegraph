/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "mygl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    MyGL *mygl;
    QTreeWidget *sceneGraph;
    QSpinBox *tX;
    QSpinBox *tY;
    QSpinBox *theta;
    QSpinBox *sX;
    QSpinBox *sY;
    QPushButton *addGeom;
    QPushButton *addT;
    QPushButton *addR;
    QPushButton *addS;
    QLabel *txLabel;
    QLabel *tyLabel;
    QLabel *sxLabel;
    QLabel *syLabel;
    QLabel *rotLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1645, 860);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QStringLiteral("mygl"));
        mygl->setGeometry(QRect(11, 11, 618, 592));
        sceneGraph = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        sceneGraph->setHeaderItem(__qtreewidgetitem);
        sceneGraph->setObjectName(QStringLiteral("sceneGraph"));
        sceneGraph->setGeometry(QRect(640, 10, 981, 591));
        sceneGraph->header()->setVisible(false);
        tX = new QSpinBox(centralWidget);
        tX->setObjectName(QStringLiteral("tX"));
        tX->setGeometry(QRect(980, 610, 161, 41));
        tX->setMinimum(-10);
        tX->setMaximum(10);
        tY = new QSpinBox(centralWidget);
        tY->setObjectName(QStringLiteral("tY"));
        tY->setGeometry(QRect(1440, 610, 181, 41));
        tY->setMinimum(-10);
        tY->setMaximum(10);
        theta = new QSpinBox(centralWidget);
        theta->setObjectName(QStringLiteral("theta"));
        theta->setGeometry(QRect(980, 680, 441, 41));
        sX = new QSpinBox(centralWidget);
        sX->setObjectName(QStringLiteral("sX"));
        sX->setGeometry(QRect(980, 750, 161, 41));
        sX->setValue(1);
        sY = new QSpinBox(centralWidget);
        sY->setObjectName(QStringLiteral("sY"));
        sY->setGeometry(QRect(1440, 750, 181, 41));
        sY->setValue(1);
        addGeom = new QPushButton(centralWidget);
        addGeom->setObjectName(QStringLiteral("addGeom"));
        addGeom->setGeometry(QRect(10, 610, 621, 51));
        addT = new QPushButton(centralWidget);
        addT->setObjectName(QStringLiteral("addT"));
        addT->setGeometry(QRect(10, 670, 201, 121));
        addR = new QPushButton(centralWidget);
        addR->setObjectName(QStringLiteral("addR"));
        addR->setGeometry(QRect(220, 670, 201, 121));
        addS = new QPushButton(centralWidget);
        addS->setObjectName(QStringLiteral("addS"));
        addS->setGeometry(QRect(430, 670, 201, 121));
        txLabel = new QLabel(centralWidget);
        txLabel->setObjectName(QStringLiteral("txLabel"));
        txLabel->setGeometry(QRect(680, 610, 291, 41));
        QFont font;
        font.setPointSize(8);
        txLabel->setFont(font);
        tyLabel = new QLabel(centralWidget);
        tyLabel->setObjectName(QStringLiteral("tyLabel"));
        tyLabel->setGeometry(QRect(1180, 610, 251, 41));
        tyLabel->setFont(font);
        sxLabel = new QLabel(centralWidget);
        sxLabel->setObjectName(QStringLiteral("sxLabel"));
        sxLabel->setGeometry(QRect(680, 750, 281, 41));
        sxLabel->setFont(font);
        syLabel = new QLabel(centralWidget);
        syLabel->setObjectName(QStringLiteral("syLabel"));
        syLabel->setGeometry(QRect(1180, 750, 231, 41));
        syLabel->setFont(font);
        rotLabel = new QLabel(centralWidget);
        rotLabel->setObjectName(QStringLiteral("rotLabel"));
        rotLabel->setGeometry(QRect(680, 680, 291, 41));
        rotLabel->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1645, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Scene Graph", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addGeom->setText(QApplication::translate("MainWindow", "+Geometry", Q_NULLPTR));
        addT->setText(QApplication::translate("MainWindow", "+Translate", Q_NULLPTR));
        addR->setText(QApplication::translate("MainWindow", "+Rotation", Q_NULLPTR));
        addS->setText(QApplication::translate("MainWindow", "+Scale", Q_NULLPTR));
        txLabel->setText(QApplication::translate("MainWindow", "X Translation:", Q_NULLPTR));
        tyLabel->setText(QApplication::translate("MainWindow", "Y Translation:", Q_NULLPTR));
        sxLabel->setText(QApplication::translate("MainWindow", "X Scale:", Q_NULLPTR));
        syLabel->setText(QApplication::translate("MainWindow", "Y Scale:", Q_NULLPTR));
        rotLabel->setText(QApplication::translate("MainWindow", "Rotation (Degrees):", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
