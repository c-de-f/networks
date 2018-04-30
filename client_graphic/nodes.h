#ifndef NODES_H
#define NODES_H
#endif
#pragma once
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QObject>
//#include "dialog.h"


class Edge;
class TheGS;

class Node: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = UserType + 1 };


    Node(QPointF c);
    ~Node();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    //bool pressed;
    QPointF position;
    QVector<Edge*> edges;
    Node* wasClicked;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void isClicked(Node*);
    void isDoubleClicked(Node*);
    //void newNode(QPointF);
    void NodeMoved(QPointF, QPointF);


};

class Edge: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Edge(Node* start, Node* end);
    QRectF boundingRect() const;
    void Move(Node* new1, Node* new2);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    Node* start;
    Node* end;
//signals:
    //void newEdge(QPointF, QPointF);
};
