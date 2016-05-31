#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <spider.h>
#include <hbserialbluetooth.h>
#include <hbtcpserver.h>
#include <hbtcpsocket.h>
#include <hbwebserver.h>

class HBTcpServer;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QCoreApplication* ap, QObject *parent = 0);
    void ConnectTcpServerSocket(HBTcpSocket *sock);
    //void commandMode(HBTcpSocket *sock);
    QThreadPool *threadpool;
    Spider *Spid;
    void OpenPorts();
    void ClosePorts();

signals:

public slots:

private:
    HBSerialBluetooth *Hbs;
    HBTcpServer *TcpServer;
    HBWebServer *WSServer;
    QCoreApplication *a;
    void ConnectSignals();
};

#endif // CONTROLLER_H
