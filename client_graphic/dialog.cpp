#include "dialog.h"
#include "ui_dialog.h"
#include <QSlider>
#include <QLayout>
#include <QGraphicsItemGroup>


void TheGS::zoomOut()
{

    for(int i = 0; i < this->views().length(); i++)
    {
        this->views()[i]->scale(1.0/1.1, 1.0/1.1);
        this->views()[i]->update();
    }
}

void TheGS::zoomIn()
{

    for(int i = 0; i < this->views().length(); i++)
    {
        this->views()[i]->scale(1.1, 1.1);
        this->views()[i]->update();
    }
}




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new TheGS();
    scene->d = this;
    scene->setSceneRect(-100, -100, 800, 500);
   // Node* n1 = new Node(QPointF(90, 90));
    //Node* n2 = new Node(QPointF(180, 180));
    //Edge* e = new Edge(n1, n2);
    //scene->addItem(n1);
    //scene->addItem(n2);
    //scene->addItem(e);

    QVBoxLayout* layoutn = new QVBoxLayout();
    QGraphicsView* v = new QGraphicsView(scene);
    layoutn->addWidget(v);
    v->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    v->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    QPushButton* b1 = new QPushButton("-");
    QPushButton* b2 = new QPushButton("+");
    //Button* b3 = new Button("New Edge");
    QHBoxLayout* l2 = new QHBoxLayout();
    b1->setGeometry(QRect(0, 385, 40, 20));
    b2->setGeometry(QRect(60, 385, 40, 20));
    l2->addWidget(b1);
    //l2->addWidget(b3);
    l2->addWidget(b2);
    layoutn->addLayout(l2);
    this->setLayout(layoutn);
    connect(b1, SIGNAL(pressed()), scene, SLOT(zoomOut()));
    connect(b2, SIGNAL(pressed()), scene, SLOT(zoomIn()));


}

Dialog::~Dialog()
{
    delete ui;
}

void TheGS::F(Node* n)
{
    if (!(this->n1)) this->n1 = n;
    else
    {
        //qDebug() << this->n1->position.x() << '\n';
        this->n2 = n;
        if (n1 == n2)
        {
            n1 = NULL;
            return;
        }

        Edge* e = new Edge(n1, n2);

        connect(this, SIGNAL(newEdge(QPointF,QPointF)), this->d, SLOT(newEdge(QPointF, QPointF)));
        emit newEdge(n1->position, n2->position);
        n1 = n2 = NULL;
        QObject::disconnect(this, 0, 0, 0);
        this->edges.append(e);
        this->addItem(e);
        this->update(sceneRect());
    }
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    //qDebug() << "I was clicked\n";

    QObject::connect(this, SIGNAL(isClicked(Node*)), (TheGS*)(this->scene()), SLOT(F(Node*)));
    emit isClicked(this);

}

void TheGS::mouseDoubleClickEvent (QGraphicsSceneMouseEvent * mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
    Node* item;

    if (item = (Node*)itemAt(mouseEvent->scenePos(), QTransform()))
    {

        item->mouseDoubleClickEvent(mouseEvent);
        //return;
    }

    else
    {
        Node* n = new Node(mouseEvent->scenePos());

        //emit n->NewNode(n->position);
        QObject::connect(this, SIGNAL(newNode(QPointF)), this->d, SLOT(newNode(QPointF)));
        emit newNode(n->position);
        QObject::disconnect(this, 0, 0, 0);
        this->nodes.append(n);
        this->addItem(n);
        this->update(sceneRect());
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
        event->accept();
        QPointF tmp = this->position;
        this->position = event->scenePos();

        QObject::connect(this, SIGNAL(NodeMoved(QPointF, QPointF)), ((TheGS*)(this->scene()))->d, SLOT(NodeMoved(QPointF, QPointF)));
        emit NodeMoved(tmp, this->position);
        QObject::disconnect(this, 0, 0, 0);
        this->scene()->update(this->scene()->sceneRect());


}



