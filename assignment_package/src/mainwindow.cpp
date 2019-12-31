#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    connect(ui->mygl, SIGNAL(sig_sendRoot(QTreeWidgetItem*)),
            this, SLOT(slot_addRootToTree(QTreeWidgetItem*)));
    connect(ui->sceneGraph, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            ui->mygl, SLOT(slot_updateCurrent(QTreeWidgetItem*, int)));
    connect(ui->addGeom, SIGNAL(clicked(bool)),
            this, SLOT(slot_addGeoToNode()));
    connect(ui->addT, SIGNAL(clicked(bool)),
            this, SLOT(slot_addTranslateNode()));
    connect(ui->addR, SIGNAL(clicked(bool)),
            this, SLOT(slot_addRotateNode()));
    connect(ui->addS, SIGNAL(clicked(bool)),
            this, SLOT(slot_addScaleNode()));
    connect(ui->tX, SIGNAL(valueChanged(int)),
            this, SLOT(slot_updateTX(int)));
    connect(ui->tY, SIGNAL(valueChanged(int)),
            this, SLOT(slot_updateTY(int)));
    connect(ui->theta, SIGNAL(valueChanged(int)),
            this, SLOT(slot_updateTheta(int)));
    connect(ui->sX, SIGNAL(valueChanged(int)),
            this, SLOT(slot_updateSX(int)));
    connect(ui->sY, SIGNAL(valueChanged(int)),
            this, SLOT(slot_updateSY(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_addRootToTree(QTreeWidgetItem *item)
{
    item->setText(0, "Root");   // w/out this line, the top item will have no text
    ui->sceneGraph->addTopLevelItem(item);
}

void MainWindow::slot_updateCurrent(QTreeWidgetItem* item)
{
    // current = (Node*)item;
}

void MainWindow::slot_addGeoToNode()
{
    if(this->ui->mygl->current->d == nullptr) {
        ui->mygl->addGeo();
    }
}

void MainWindow::slot_updateTX(int tx)
{
    TranslateNode* currTrans = dynamic_cast<TranslateNode*>(this->ui->mygl->current);
    if (currTrans != nullptr)
    {
        currTrans->x = tx;
    }
    currentTX = tx;
}

void MainWindow::slot_updateTY(int ty)
{
    TranslateNode* currTrans = dynamic_cast<TranslateNode*>(this->ui->mygl->current);
    if (currTrans != nullptr)
    {
        currTrans->y = ty;
    }
    currentTY = ty;
}

void MainWindow::slot_updateTheta(int theta)
{
    RotateNode* currRot = dynamic_cast<RotateNode*>(this->ui->mygl->current);
    if (currRot != nullptr)
    {
        currRot->theta = theta;
    }
    currentTheta = theta;
}

void MainWindow::slot_updateSX(int sx)
{
    ScaleNode* currScale = dynamic_cast<ScaleNode*>(this->ui->mygl->current);
    if (currScale != nullptr)
    {
        currScale->x = sx;
    }
    currentSX = sx;
}

void MainWindow::slot_updateSY(int sy)
{
    ScaleNode* currScale = dynamic_cast<ScaleNode*>(this->ui->mygl->current);
    if (currScale != nullptr)
    {
        currScale->y = sy;
    }
    currentSY = sy;
}

void MainWindow::slot_addTranslateNode()
{
    uPtr<TranslateNode> t = mkU<TranslateNode>(nullptr, glm::vec3(0, 0, 0),
                                      this->ui->mygl->current->name + "-T",
                                      currentTX, currentTY);
    this->ui->mygl->current->adopt(std::move(t));
}

void MainWindow::slot_addRotateNode()
{
    uPtr<RotateNode> r = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      this->ui->mygl->current->name + "-R",
                                      currentTheta);
    this->ui->mygl->current->adopt(std::move(r));
}

void MainWindow::slot_addScaleNode()
{
    uPtr<ScaleNode> s = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0),
                                      this->ui->mygl->current->name + "-S",
                                      currentSX, currentSY);
    // std::cout << s->x << " " << s->y << std::endl;
    this->ui->mygl->current->adopt(std::move(s));
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}
