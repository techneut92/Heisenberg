#include "hbtcpserver.h"

HBTcpServer::HBTcpServer(quint16 port, Controller *cptr)
{
    if (this->listen(QHostAddress::Any, port))
        qDebug() << "Tcp server connected at " << port;
    else
        qDebug() << "Failed to start!";
    this->ControllerPtr = cptr;
}

HBTcpServer::~HBTcpServer(){

}

void HBTcpServer::incomingConnection(qintptr handle){
    qDebug() << "New incoming connection " << handle;
    HBTcpSocket *socket = new HBTcpSocket(this->ControllerPtr);
    socket->SetSocket(handle);
    TcpClients << socket;
}

