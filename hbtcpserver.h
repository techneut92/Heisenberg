#ifndef HBTCPSERVER_H
#define HBTCPSERVER_H

#include <QObject>
#include <controller.h>
#include <QTcpServer>
#include <QDebug>
#include <hbtcpsocket.h>

class Controller;
class HBTcpSocket;

class HBTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HBTcpServer(quint16 port, Controller *cptr);
    ~HBTcpServer();

private:
    Controller* ControllerPtr;

protected:
    void incomingConnection(qintptr handle);
    QList<HBTcpSocket*> TcpClients;

signals:


public slots:
};

#endif // HBTCPSERVER_H
