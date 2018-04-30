#include <QtGui>
#include <QtNetwork>

#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QByteArray>
#include "server.h"

TCPServer::TCPServer(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("TCP Server");

    server=new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(processNewConnection()));

    QFormLayout *layout=new QFormLayout(this);

    host=new QLineEdit("127.0.0.1", this);
    layout->addRow("Host:", host);

    port=new QSpinBox(this);
    port->setRange(0,9999);
    port->setValue(5000);
    layout->addRow("Port:", port);

    control=new QPushButton("Start", this);
    connect(control, SIGNAL(clicked()), this, SLOT(start()));
    layout->addWidget(control);

    trace=new QTextEdit(this);
    trace->setReadOnly(true);
    layout->addWidget(trace);
}

void TCPServer::start(){
    if(server->isListening()) return;

    if(!server->listen(QHostAddress(host->text()), port->value()))
        trace->append("Failed to listen!");
    else trace->append("Listening!");
}

void TCPServer::processNewConnection(){
    while(server->hasPendingConnections()){
        trace->append("Accepting connection!");
        QTcpSocket *socket=server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), this, SLOT(readClient()));
        sockets.append(socket);
    }
}

void TCPServer::readClient(){
    QTcpSocket *socket=dynamic_cast<QTcpSocket*>(sender());
    //socket->write(QString("Hello Client").toLatin1());
    QByteArray s = socket->readAll();
    trace->append(s);
    for (int i = 0; i < sockets.length(); i++)
        if (sockets[i] != socket) sockets[i]->write(s);


}
