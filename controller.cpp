#include "controller.h"

Controller::Controller(QCoreApplication *ap, QObject *parent) : QObject(parent)
{
    this->Hbs = new HBSerialBluetooth();
    this->WSServer = new HBWebServer(WEBSOCKETSERVER_PORT);
    this->Spid = new Spider();
    this->TcpServer = new HBTcpServer(TCP_PORT, this);
    this->a = ap;

    this->Spid->setAutoDelete(false);
    this->threadpool = QThreadPool::globalInstance();
    this->threadpool->start(this->Spid);
    this->ConnectSignals();
}

void Controller::ConnectSignals(){
    QObject::connect(this->Hbs, SIGNAL(SendCommand(quint16)), this->Spid, SLOT(SetCommand(quint16)));
    QObject::connect(this->a, SIGNAL(aboutToQuit()), this->Hbs, SLOT(ClosePorts()));
}

void Controller::ConnectTcpServerSocket(HBTcpSocket *sock){
    connect(this->Spid, SIGNAL(Walk(quint8)), sock, SLOT(SendWalk(quint8)));
}

/*
void Controller::commandMode(HBTcpSocket* sock){
    connect(sock, SIGNAL(SendCommand(quint16)), this->Spid, SLOT(SetCommand(quint16)));
}
*/

void Controller::OpenPorts(){
    this->Hbs->OpenPorts();
}

void Controller::ClosePorts(){
    this->Hbs->ClosePorts();
}
