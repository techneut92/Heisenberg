#include "hbwebserver.h"

QT_USE_NAMESPACE

HBWebServer::HBWebServer(quint16 port, QObject *parent) :
    QObject(parent),
    HBWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this))
{
    if (HBWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "WebSocket Server listening on port" << port;
        connect(HBWebSocketServer, &QWebSocketServer::newConnection,this, &HBWebServer::onNewConnection);
        connect(HBWebSocketServer, &QWebSocketServer::closed, this, &HBWebServer::closed);
    }
}

HBWebServer::~HBWebServer()
{
    HBWebSocketServer->close();
    qDeleteAll(HBClients.begin(), HBClients.end());
}
void HBWebServer::onNewConnection()
{
    QWebSocket *pSocket = HBWebSocketServer->nextPendingConnection();

    qDebug() << "New Connection" << pSocket->peerAddress() << ":" << pSocket->peerPort();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &HBWebServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &HBWebServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &HBWebServer::socketDisconnected);

    HBClients << pSocket;
}

void HBWebServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Message received:" << message;
    if (pClient) {
        pClient->sendTextMessage(message);
    }
}

void HBWebServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void HBWebServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        HBClients.removeAll(pClient);
        pClient->deleteLater();
    }
}
