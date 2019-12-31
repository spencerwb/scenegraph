#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

#include "node.h"
#include "smartpointerhelp.h"

MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      prog_flat(this),
      m_geomGrid(this), m_geomSquare(this, {glm::vec3(0.5f, 0.5f, 1.f),
                                            glm::vec3(-0.5f, 0.5f, 1.f),
                                            glm::vec3(-0.5f, -0.5f, 1.f),
                                            glm::vec3(0.5f, -0.5f, 1.f)}),
      m_showGrid(true)
{
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();

    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_geomGrid.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the scene geometry
    m_geomGrid.create();
    m_geomSquare.create();

    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    this->root = ScaleNode(nullptr, glm::vec3(), QString("Root"), 0.5, 0.5);
    this->current = &(this->root);
    prevCurrCol = current->color;
    construct();
    emit sig_sendRoot(&(this->root));
}

void MyGL::resizeGL(int w, int h)
{
    glm::mat3 viewMat = glm::scale(glm::mat3(), glm::vec2(0.2, 0.2)); // Screen is -5 to 5

    // Upload the view matrix to our shader (i.e. onto the graphics card)
    prog_flat.setViewMatrix(viewMat);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_showGrid)
    {
        prog_flat.setModelMatrix(glm::mat3());
        prog_flat.draw(*this, m_geomGrid);
    }

    //VVV CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL VVV///////////////////

    // Shapes will be drawn on top of one another, so the last object
    // drawn will appear in front of everything else

//    prog_flat.setModelMatrix(glm::mat3());
//    m_geomSquare.setColor(glm::vec3(0,1,0));
//    prog_flat.draw(*this, m_geomSquare);

//    m_geomSquare.setColor(glm::vec3(1,0,0));
//    prog_flat.setModelMatrix(glm::translate(glm::mat3(), glm::vec2(-1.f, 0.f)) * glm::rotate(glm::mat3(), glm::radians(-30.f)));
//    prog_flat.draw(*this, m_geomSquare);

//    m_geomSquare.setColor(glm::vec3(0,0,1));
//    prog_flat.setModelMatrix(glm::translate(glm::mat3(), glm::vec2(1.f, 0.f)) * glm::rotate(glm::mat3(), glm::radians(30.f)));
//    prog_flat.draw(*this, m_geomSquare);

    //^^^^^^^ CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL ^^^^^^^//

    // Here is a good spot to call your scene graph traversal function.
    // Any time you want to draw an instance of geometry, call
    // prog_flat.draw(*this, yourNonPointerGeometry);
    glm::mat3 m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    traverse(this->root, m);
}

Node& MyGL::construct()
{
    // angular displacements of left and right elbows and shoulders in degrees
    float thetaLA = 90;
    float thetaLB = -45;
    float thetaRA = -90;
    float thetaRB = 45;
    float thetaH = 0;

    // left shoulder
    uPtr<Node> l_shoulder = mkU<TranslateNode>(nullptr, glm::vec3(0, 0, 0),
                                               "L_shoulder-T", -1, 0);
    // left forearm
    uPtr<Node> lA23 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "LA23-R",thetaLA);
    uPtr<Node> lA12 = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0),
                                     "LA12-S", 2, 1);
    uPtr<Node> lA01 = mkU<TranslateNode>(&m_geomSquare, glm::vec3(0, 1, 0),
                                         "LA01-T", -0.5, 0);
    // left upperarm
    uPtr<Node> lB45 = mkU<TranslateNode>(nullptr, glm::vec3(0, 0, 0),
                                         "LB45-T", -2*cos(glm::radians(thetaLA)),
                                         -2*sin(glm::radians(thetaLA)));
    uPtr<Node> lB34 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "LB34-R",thetaLB);
    uPtr<Node> lB23 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "LB23-R",thetaLA);
    uPtr<Node> lB12 = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0),
                                     "LB12-S",2, 1);
    uPtr<Node> lB01 = mkU<TranslateNode>(&m_geomSquare, glm::vec3(0, 0, 1),
                                         "LB01-T", -0.5, 0);
    // left arm adoption/assembly
    lA12->adopt(std::move(lA01));
    lA23->adopt(std::move(lA12));
    lB12->adopt(std::move(lB01));
    lB23->adopt(std::move(lB12));
    lB34->adopt(std::move(lB23));
    lB45->adopt(std::move(lB34));
    l_shoulder->adopt(std::move(lA23));
    l_shoulder->adopt(std::move(lB45));

    // right shoulder
    uPtr<Node> r_shoulder = mkU<TranslateNode>(nullptr, glm::vec3(),
                                               "r_shoulder-T",1, 0);

    // right forearm
    uPtr<Node> rA23 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "RA23-R", thetaRA);
    uPtr<Node> rA12 = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0),
                                     "RA12-S", 2, 1);
    uPtr<Node> rA01 = mkU<TranslateNode>(&m_geomSquare, glm::vec3(0, 1, 0),
                                         "RA01-T", 0.5, 0);
    // right upperarm
    uPtr<Node> rB45 = mkU<TranslateNode>(nullptr, glm::vec3(0, 0, 0),
                                         "RB45-T", 2*cos(glm::radians(thetaRA)),
                                         2*sin(glm::radians(thetaRA)));
    uPtr<Node> rB34 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "RB34-R", thetaRB);
    uPtr<Node> rB23 = mkU<RotateNode>(nullptr, glm::vec3(0, 0, 0),
                                      "RB23-R", thetaRA);
    uPtr<Node> rB12 = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0),
                                     "RB12-S", 2, 1);
    uPtr<Node> rB01 = mkU<TranslateNode>(&m_geomSquare, glm::vec3(0, 0, 1),
                                         "RB01-T", 0.5, 0);
    // right arm adoption/assembly
    rA12->adopt(std::move(rA01));
    rA23->adopt(std::move(rA12));
    rB12->adopt(std::move(rB01));
    rB23->adopt(std::move(rB12));
    rB34->adopt(std::move(rB23));
    rB45->adopt(std::move(rB34));
    r_shoulder->adopt(std::move(rA23));
    r_shoulder->adopt(std::move(rB45));

    // torso
    uPtr<Node> t0 = mkU<ScaleNode>(&m_geomSquare, glm::vec3(1, 0, 0), "T0-S",
                                      2, 3);
    uPtr<Node> torso = mkU<TranslateNode>(nullptr, glm::vec3(),
                                          "torso-T", 0, -1);

    // head
    uPtr<Node> h0 = mkU<TranslateNode>(&m_geomSquare, glm::vec3(0, 1, 0), "H0-T",
                                         0, 2);
    uPtr<Node> head = mkU<RotateNode>(nullptr, glm::vec3(),
                                      "head-R",thetaH);

    // head assembly
    head->adopt(std::move(h0));

    // torso undos
    uPtr<Node> tZ0 = mkU<ScaleNode>(nullptr, glm::vec3(0, 0, 0), "TZ0-S",
                                    0.5, 1.f/3.f);
    uPtr<Node> tZ1 = mkU<TranslateNode>(nullptr, glm::vec3(0, 0, 0), "TZ1-T",
                                        0, 1.f/3.f);

    // body assembly
    tZ0->adopt(std::move(r_shoulder));
    tZ0->adopt(std::move(l_shoulder));
    tZ0->adopt(std::move(head));
    tZ1->adopt(std::move(tZ0));
    t0->adopt(std::move(tZ1));
    torso->adopt(std::move(t0));
    root.adopt(std::move(torso));

    return root;
}

void MyGL::traverse(Node& n, glm::mat3 m)
{
    m = m * n.transformation();
    for (const uPtr<Node>& child : n.children)
    {
        traverse(*child, m);
    }
    if (n.d)
    {
        ((Polygon2D*)((n.d)))->setColor(n.color);
        prog_flat.setModelMatrix(m);
        prog_flat.draw(*this, *n.d);
    }
}

boolean MyGL::addGeo()
{
    current->d = &(this->m_geomSquare);
    return (current->d) != nullptr;
}

void MyGL::slot_updateCurrent(QTreeWidgetItem* i, int n)
{
    current->color = prevCurrCol;
    current = ((Node*)i);
    prevCurrCol = current->color;
    current->color = glm::vec3(1, 1, 0);
}

void MyGL::keyPressEvent(QKeyEvent *e)
{
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    switch(e->key())
    {
    case(Qt::Key_Escape):
        QApplication::quit();
        break;

    case(Qt::Key_G):
        m_showGrid = !m_showGrid;
        break;
    }
}
