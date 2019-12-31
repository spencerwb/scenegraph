#ifndef NODE_H
#define NODE_H

#include "smartpointerhelp.h"
#include "drawable.h"
#include <QString>
#include <QTreeWidgetItem>


class Node : public QTreeWidgetItem
{
public:
    std::vector<uPtr<Node>> children;
    Drawable* d;
    glm::vec3 color;
    QString name;

    Node();
    Node(Drawable*, glm::vec3, QString);
    Node(const Node& n);
    virtual ~Node();
    void operator=(const Node&);
    virtual glm::mat3 transformation() = 0;
    Node& adopt(uPtr<Node> p);
    glm::vec3 colorChange(glm::vec3 c);
};


class TranslateNode : public Node
{
public:
    // translation in the x and y directions
    float x, y;

    TranslateNode();
    TranslateNode(float, float);
    TranslateNode(Drawable*, glm::vec3, QString, float, float);
    TranslateNode(const TranslateNode& tn);
    virtual ~TranslateNode();
    void operator=(const TranslateNode&);
    virtual glm::mat3 transformation();
};


class RotateNode : public Node
{
public:
    // magnitude of rotation in degrees
    float theta;

    RotateNode();
    RotateNode(float);
    RotateNode(Drawable*, glm::vec3, QString, float);
    RotateNode(const RotateNode&);
    virtual ~RotateNode();
    void operator=(const RotateNode&);
    virtual glm::mat3 transformation();
};


class ScaleNode : public Node
{
public:
    // scale in the x and y directions
    float x, y;

    ScaleNode();
    ScaleNode(float x, float y);
    ScaleNode(Drawable*, glm::vec3, QString, float, float);
    ScaleNode(const ScaleNode& sn);
    virtual ~ScaleNode();
    void operator=(const ScaleNode&);
    virtual glm::mat3 transformation();
};

#endif // NODE_H
