#include "hbtcpsocket.h"
#include <QThread>
#include <QtConcurrent>

HBTcpSocket::HBTcpSocket(Controller *cptr)
{
    this->Mode = NoModeSet;
    this->ControllerPtr = cptr;
}

HBTcpSocket::~HBTcpSocket(){

}

void HBTcpSocket::ReadyRead(){
    QString data = socket->readAll();
    qDebug() << data;
    if (data.startsWith("COMMANDCENTER")) {
        qDebug() << "New Command console attached";
        this->Mode = ConsoleMode;
        this->CCenter = new HBCommandCenter(this->socket);
        connect(this->CCenter, SIGNAL(IsDone()), this, SLOT(ConsoleCommandDone()));
        connect(this->CCenter, SIGNAL(SendCommand(quint16)), this->ControllerPtr->Spid, SLOT(SetCommand(quint16)));
        this->ControllerPtr->threadpool->start(this->CCenter);
    }

    else if (data.startsWith("LEGMODE")){
        qDebug() << "Spider legs attached.";
        this->Mode = LegMode;
        this->ControllerPtr->ConnectTcpServerSocket(this);
        socket->write("spiderlegs connected");
    }
    else if (data.toLower().startsWith("exit")) socket->~QTcpSocket();
    else if (this->Mode == ConsoleMode) this->CCenter->ParseConsoleCommand(data);
    else if (this->Mode == LegMode) this->ParseLegData(data) ;
    else if (this->Mode == NoModeSet) qDebug() << "No mode is set. enter LEGMODE or COMMANDCENTER first." ;
    else qDebug() << "Something is very very wrong";
    //qDebug() << data;
}

void HBTcpSocket::Disconnected(){
    QString mode = this->Mode == ConsoleMode ? "Console" : this->Mode == LegMode ? "Legs" : this->Mode == NoModeSet ? "Unset tcp socket": "something";
    qDebug() << mode << " disconnected from spider";
}

void HBTcpSocket::Connected(){

}

void HBTcpSocket::SetSocket(int socketDescriptor){
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));

    socket->setSocketDescriptor(socketDescriptor);
}

void HBTcpSocket::SendWalk(quint8 command){
    QString data;
    switch(command){
    case 1:
        data = "forward";
        break;
    case 2:
        data = "backward";
        break;
    case 3:
        data = "turnleft";
        break;
    case 4:
        data = "turnright";
        break;
    }

    this->socket->write(data.toStdString().c_str());
    this->socket->flush();
}

bool HBTcpSocket::GetConsoleMode(){
    return this->ConsoleMode;
}

void HBTcpSocket::ConsoleCommandDone(){
    this->socket->write("heisenberg>> ");
}

void HBTcpSocket::ParseLegData(QString data){

}
