#pragma once

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "smartpointerhelp.h"
#include "node.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void slot_addRootToTree(QTreeWidgetItem*);
    void slot_updateCurrent(QTreeWidgetItem*);
    void slot_addGeoToNode();
    void slot_updateTX(int);
    void slot_updateTY(int);
    void slot_updateTheta(int);
    void slot_updateSX(int);
    void slot_updateSY(int);
    void slot_addTranslateNode();
    void slot_addRotateNode();
    void slot_addScaleNode();

public:
    // uPtr<Node> current;
    // Node* current;
    float currentTX;
    float currentTY;
    float currentTheta;
    float currentSX;
    float currentSY;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
};
