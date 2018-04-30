#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class QTcpServer;
class QTcpSocket;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QTextEdit;

class TCPServer : public QWidget
{
    Q_OBJECT
public:
    explicit TCPServer(QWidget *parent = 0);

private:
    QTcpServer *server;
    QList<QTcpSocket*> sockets;
    QLineEdit *host;
    QSpinBox *port;
    QPushButton *control;
    QTextEdit *trace;

public slots:
    void start();
    void processNewConnection();
    void readClient();
};

#endif // SERVER_H
