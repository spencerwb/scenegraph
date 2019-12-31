#include "node.h"
#include "smartpointerhelp.h"
// #include <math.h>

//************************* Node *************************//

Node::Node()
    : QTreeWidgetItem(), children(std::vector<uPtr<Node>>()), d(nullptr),
      color({0, 0, 0}), name("")
{
    setText(0, name);
}

Node::Node(Drawable* d, glm::vec3 c, QString n)
    : QTreeWidgetItem(), children(std::vector<uPtr<Node>>()), d(d),
      color(c), name(n)
{
    setText(0, name);
}

Node::Node(const Node &n)
    : QTreeWidgetItem(), children(std::vector<uPtr<Node>>()), d(n.d),
      color(n.color), name(n.name)
{
    setText(0, name);
}

void Node::operator=(const Node &n)
{
    this->children = std::vector<uPtr<Node>>();
    this->d = n.d;
    this->color = n.color;
    this->name = n.name;
}

Node& Node::adopt(uPtr<Node> p)
{
    QTreeWidgetItem::addChild(p.get());
    uPtr<Node> newChild = std::move(p);
    children.push_back(std::move(newChild));
    return *(children.back());
    // So right now we have both a Uptr and a reference pointing
    // to the same memory on the heap. Yikes.
}

glm::vec3 Node::colorChange(glm::vec3 c)
{
    glm::vec3 oldColor = color;
    color = c;
    return oldColor;
}

Node::~Node()
{}

//*********************** TranslateNode ***********************//

TranslateNode::TranslateNode()
    : Node(), x(0), y(0)
{}

TranslateNode::TranslateNode(float x, float y)
    : Node(), x(x), y(y)
{}

TranslateNode::TranslateNode(Drawable* d, glm::vec3 c, QString n,
                             float x, float y)
    : Node(d, c, n), x(x), y(y)
{}

TranslateNode::TranslateNode(const TranslateNode &tn)
    : Node(tn), x(tn.x), y(tn.y)
{}

void TranslateNode::operator=(const TranslateNode &tn)
{
    this->Node::operator =(tn);
    this->x = tn.x;
    this->y = tn.y;
}

glm::mat3 TranslateNode::transformation()
{
    return glm::mat3({{1, 0, 0}, {0, 1, 0}, {x, y, 1}});
}

TranslateNode::~TranslateNode()
{}


//*********************** RotateNode ***********************//

RotateNode::RotateNode()
    : Node(), theta(0)
{}

RotateNode::RotateNode(float theta)
    : Node(), theta(theta)
{}

RotateNode::RotateNode(Drawable* d, glm::vec3 c, QString n, float theta)
    : Node(d, c, n), theta(theta)
{}

RotateNode::RotateNode(const RotateNode &rn)
    : Node(rn), theta(rn.theta)
{}

void RotateNode::operator =(const RotateNode &rn)
{
    this->Node::operator =(rn);
    this->theta = rn.theta;
}

glm::mat3 RotateNode::transformation()
{
    float theta = this->theta * M_PI / 180;
    return glm::mat3({{cos(theta),  sin(theta), 0},
                      {-sin(theta), cos(theta), 0},
                      {0,           0,          1}});
}

RotateNode::~RotateNode()
{}

//*********************** ScaleNode ***********************//

ScaleNode::ScaleNode()
    : Node(), x(1), y(1)
{}

ScaleNode::ScaleNode(float x, float y)
    : Node(), x(x), y(y)
{}

ScaleNode::ScaleNode(Drawable* d, glm::vec3 c, QString n,
                             float x, float y)
    : Node(d, c, n), x(x), y(y)
{}

ScaleNode::ScaleNode(const ScaleNode &sn)
    : Node(sn), x(sn.x), y(sn.y)
{}

void ScaleNode::operator =(const ScaleNode &sn)
{
    this->Node::operator =(sn);
    this->x = sn.x;
    this->y = sn.y;
}

glm::mat3 ScaleNode::transformation()
{
    return glm::mat3({{x, 0, 0}, {0, y, 0}, {0, 0, 1}});
}

ScaleNode::~ScaleNode()
{}
