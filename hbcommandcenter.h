#ifndef HBCOMMANDCENTER_H
#define HBCOMMANDCENTER_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QTimer>
#include <controller.h>

class Controller;

class HBCommandCenter : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit HBCommandCenter(QTcpSocket *sock, QObject *parent = 0);
    void ParseConsoleCommand(QString data);
    enum ModeSet{
        EmitWalk,
        Idle,
        SetController,
        NoModeSet
    };
private:
    QTcpSocket* Socket;
    ModeSet Mode;
    QString Data;
    Controller* ControllerPtr;
    void run();

signals:
    void SendCommand(quint16 command);
    void IsDone();
};

#endif // HBCOMMANDCENTER_H
