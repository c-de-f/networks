#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QWidget>
#include "dialog.h"

class QTcpSocket;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QTextEdit;

class TCPClient : public Dialog
{
    Q_OBJECT

public:
    TCPClient(QWidget *parent = 0);

private:
    QTcpSocket *socket;
    QLineEdit *host;
    QSpinBox *port;
    QPushButton *control;
    QTextEdit *trace;

public slots:
    void connectToHost();
    void connected();
    void readServer();
    void newNode(QPointF);
    void NodeMoved(QPointF, QPointF);
    void newEdge(QPointF, QPointF);
};

#endif // CLIENT_H
