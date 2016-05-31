#ifndef HBTCPSOCKET_H
#define HBTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <controller.h>
#include <hbcommandcenter.h>

class Controller;
class HBCommandCenter;

class HBTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit HBTcpSocket(Controller *cptr);
    ~HBTcpSocket();
    void SetSocket(int socketDescriptor);
    bool GetConsoleMode();
    enum SocketTypes{
        NoModeSet,
        LegMode,
        ConsoleMode
    };

private:
    QTcpSocket *socket;
    SocketTypes Mode;
    Controller *ControllerPtr;
    HBCommandCenter *CCenter;
    void ParseConsoleCommand(QString data);
    void ParseLegData(QString data);

signals:
    //void SendCommand(quint16);

public slots:
    void ReadyRead();
    void Disconnected();
    void Connected();
    void SendWalk(quint8 command);
    void ConsoleCommandDone();
};


#endif // HBTCPSOCKET_H
