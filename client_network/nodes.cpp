#include "nodes.h"
#pragma once
#define RADIUS QPointF(20.0, 20.0)

Node::Node(QPointF pt) : QGraphicsItem::QGraphicsItem(Q_NULLPTR)
{
    setFlag(ItemIsMovable);
    this->edges = QVector<Edge*>(0);
    this->position = pt;
    this->wasClicked = NULL;
    this->setZValue(10);
    //QObject::connect(this, SIGNAL(isClicked(Node*)), (TheGS*)(this->scene()), SLOT(F(Node*)));
    //emit NewNode(position);
    //(this, SIGNAL(NewNode(QPointF)), this->scene()->d, SLOT(NewNode(QPointF)));
}

Node::~Node()
{

}

QRectF Node::boundingRect() const
{
    return QRectF(position - RADIUS, position + RADIUS);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF r = this->Node::boundingRect();
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(r);
}





Edge::Edge(Node *start, Node *end) : QGraphicsItem::QGraphicsItem(Q_NULLPTR)
{
    setFlag(ItemIsMovable);
    this->start = start;
    this->end = end;
    start->edges.append(this);
    end->edges.append(this);

}

QRectF Edge::boundingRect() const
{
    qreal x1 = qMin(this->start->position.x(), this->end->position.x());
    qreal y1 = qMin(this->start->position.y(), this->end->position.y());
    qreal x2 = qMax(this->start->position.x(), this->end->position.x());
    qreal y2 = qMax(this->start->position.y(), this->end->position.y());

    return QRectF(QPointF(x1, y1), QPointF(x2, y2));
}


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawLine(QLineF(start->position, end->position));
}
