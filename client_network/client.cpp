#include "client.h"
#include <QDebug>
#include <QtGui>
#include <QtNetwork>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QByteArray>
#define NUM QByteArray::number
#define SPACE QByteArray(" ")

TCPClient::TCPClient(QWidget *parent)
    : Dialog(parent)
{
    setWindowTitle("TCP Client");

    socket=new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readServer()));

    QFormLayout *layout=new QFormLayout(this);

    host=new QLineEdit("127.0.0.1", this);
    layout->addRow("Host:", host);

    port=new QSpinBox(this);
    port->setRange(0,9999);
    port->setValue(5000);
    layout->addRow("Port:", port);

    control=new QPushButton("Connect", this);
    connect(control, SIGNAL(clicked()), this, SLOT(connectToHost()));
    layout->addWidget(control);

    trace=new QTextEdit(this);
    trace->setReadOnly(true);
    layout->addWidget(trace);
    ((QVBoxLayout*)(this->layout()))->addLayout(layout);

}

void TCPClient::connectToHost(){
    socket->connectToHost(QHostAddress(host->text()), port->value());
}

void TCPClient::connected(){
    //socket->write(QString("Hello Server").toLatin1());
    trace->append("Connected");
    //socket->waitForBytesWritten();
}

void TCPClient::readServer(){
    //qDebug() << "here\n";
    QPointF a, b;
    QByteArray s = socket->readAll();
    qDebug() << s;
    //trace->append(s);
    int tmp = s.indexOf(" ");
    int l = s.left(tmp).toInt();
    int tmp2 = s.indexOf(" ", tmp + 1);
    a.setX(s.mid(tmp, tmp2 - tmp).toInt());
    tmp = tmp2;
    tmp2 = s.indexOf(" ", tmp + 1);
    a.setY(s.mid(tmp, tmp2 - tmp).toInt());
    qDebug() << a.y();
    if (l != 1)
    {
        tmp = tmp2;
        tmp2 = s.indexOf(" ", tmp + 1);
        b.setX(s.mid(tmp, tmp2 - tmp).toInt());
        tmp = tmp2;
        tmp2 = s.indexOf(" ", tmp + 1);
        b.setY(s.mid(tmp, tmp2 - tmp).toInt());
        //qDebug() << b.y();
    }

    if (l == 1)
    {
        Node *n = new Node(a);
        this->scene->addItem(n);
        this->scene->nodes.append(n);

    }
    if (l == 2)
    {

        for (int i = 0; i < this->scene->nodes.length(); i++)
            if (this->scene->nodes[i]->position == a)
                this->scene->nodes[i]->position = b;
        this->scene->update(this->scene->sceneRect());
    }
    if (l == 3)
    {
        qDebug() << this->scene->nodes.length();
        Node* n1;
        Node* n2;
        for (int i = 0; i < this->scene->nodes.length(); i++)
        {
            if (this->scene->nodes[i]->position == a) n1 = this->scene->nodes[i];
            else if (this->scene->nodes[i]->position == b) n2 = this->scene->nodes[i];
        }

        Edge* e = new Edge(n1, n2);
        this->scene->addItem(e);
        this->scene->edges.append(e);
    }

}

void TCPClient::newNode(QPointF a)
{
   // qDebug() << "new node at " << a << "\n";
    QObject::disconnect(this, SIGNAL(newNode(QPointF)), 0, 0);
    QByteArray sendInfo, tmp;
    sendInfo = NUM(1) + SPACE + NUM(a.x()) + SPACE + NUM(a.y());

    socket->write(sendInfo);
}

void TCPClient::NodeMoved(QPointF a, QPointF b)
{
   // qDebug() << "node " << a << " moved to " << b << "\n";
    QObject::disconnect(this, SIGNAL(NodeMoved(QPointF, QPointF)), 0, 0);
    QByteArray sendInfo;
    sendInfo = NUM(2) + SPACE + NUM(a.x()) + SPACE + NUM(a.y()) + SPACE + NUM(b.x()) + SPACE + NUM(b.y());

    socket->write(sendInfo);
}

void TCPClient::newEdge(QPointF a, QPointF b)
{
   // qDebug() << "edge " << a << " to " << b << "\n";
    QObject::disconnect(this, SIGNAL(newEdge(QPointF, QPointF)), 0, 0);
    QByteArray sendInfo;
     sendInfo = NUM(3) + SPACE + NUM(a.x()) + SPACE + NUM(a.y()) + SPACE + NUM(b.x()) + SPACE + NUM(b.y());
    socket->write(sendInfo);
}
