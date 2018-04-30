#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

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
   // exit(0);
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    std::string msg = message.toUtf8().constData();
    Problem* p = new Problem(msg, 0);
    MixedSolver s(p, NULL, 4, 2);
    s.solve();
    std::string res = "Makespan: " + std::to_string(s.solution.second) + "\n";
    for (auto &i : s.solution.first) res += std::to_string(i.second.start()) + ' ';
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
