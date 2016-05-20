#ifndef HBWEBSERVER_H
#define HBWEBSERVER_H

#include <QObject>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class HBWebServer : public QObject
{
    Q_OBJECT
public:
    explicit HBWebServer(quint16 port, QObject *parent = Q_NULLPTR);
    ~HBWebServer();

private:
    QWebSocketServer *HBWebSocketServer;
    QList<QWebSocket *> HBClients;

signals:
    void closed();

public slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

};

#endif // HBWEBSERVER_H
