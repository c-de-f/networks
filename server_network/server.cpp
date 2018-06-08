#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <string.h>

QT_USE_NAMESPACE

EchoServer::EchoServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }
}

EchoServer::~EchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void EchoServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &EchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);

    m_clients << pSocket;
}

void EchoServer::processTextMessage(QString message)
{
  //  qDebug() << "msg equals " << message << '\n';
   //exit(0);
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
   // exit(0);

      //  qDebug() << "Message received:" << message;
 //   exit(0);
    std::string m = message.toUtf8().constData();
    Problem* p;
    if (m[0] == 'P') { p = new Problem(m); qDebug() << message << '\n';}
    else p = new Problem(m, 0);
    Solver* s = NULL;
    int sz = p->tasks.size();
//    qDebug() << sz << '\n';
     pClient->sendTextMessage(QString::fromUtf8((std::to_string(sz) + " tasks received").c_str()));
    Heuristics* h = new SimpleHeuristics(2);
    if (sz < 5) { s = new ExactSolver(p, h); }
    else if (sz < 7) { s = new MixedSolver(p, h, 3, 2);}
    else if (sz < 30) { s = new MixedSolver(p, h, 1, 2);}
    else {/*qDebug() << "4\n";*/ s = new HeurSolver(p, h);}
    s->solve();
    //qDebug() << s->solution.second << '\n';
    float sol = s->solution.second;
   // qDebug() << sol << sol << '\n';
    std::string res = "Makespan: " + std::to_string(sol) + "\n";
    for (auto &i : s->solution.first) res += std::to_string(i.second.start()) + ' ';
    res+='\n';
    if (pClient) {

        pClient->sendTextMessage(QString::fromUtf8(res.c_str()));
    }
}

void EchoServer::processBinaryMessage(QByteArray message)
{

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    pClient->sendTextMessage(message);
    //exit(0);

    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    pClient->sendTextMessage("test");
   /* if (pClient) {

        pClient->sendBinaryMessage(message);
    }*/
}

void EchoServer::socketDisconnected()
{

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
