#ifndef DIALOG_H
#define DIALOG_H
#pragma once
#include <QDialog>
#include <QVector>
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QGraphicsScene>
#include "nodes.h"
class Node;
namespace Ui {
class Dialog;
}

class Dialog;

class TheGS: public QGraphicsScene
{
    Q_OBJECT
public:
    //TheGS(Dialog* d) : QGraphicsScene::QGraphicsScene(d)
    TheGS() : QGraphicsScene::QGraphicsScene()
    {

        nodes = QVector<Node*>();
        edges = QVector<Edge*>();
    }

    ~TheGS()
    {

    }
    Node* n1;
    Node* n2;
    Dialog* d;

    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * mouseEvent);
    QVector<Node*> nodes;
    QVector <Edge*> edges;
public slots:
    void zoomOut();
    void zoomIn();
    void F(Node*);
signals:
    void newNode(QPointF);
    void newEdge(QPointF, QPointF);


};


class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

//private:
    Ui::Dialog *ui;
    TheGS* scene;

};




#endif // DIALOG_H
