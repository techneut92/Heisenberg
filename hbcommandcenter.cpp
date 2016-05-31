#include "hbcommandcenter.h"

HBCommandCenter::HBCommandCenter(QTcpSocket *sock, QObject *parent)
{
    this->Socket = sock;
    this->Socket->write("Console mode entered\r\nheisenberg>> ");
    this->Mode = NoModeSet;
}

void HBCommandCenter::run(){
    while(true){
        if (this->Mode == NoModeSet) {}
        else if (this->Mode == EmitWalk && this->Data != "") {
            QList<QString> datalist = this->Data.split(" ");
            QTimer timer;
            quint8 sCommand;
            if (datalist[1].toLower() == "f") sCommand = 1;
            else if (datalist[1].toLower() == "b") sCommand = 2;
            else if (datalist[1].toLower() == "l") sCommand = 3;
            else if (datalist[1].toLower() == "r") sCommand = 4;
            bool running = true;
            while (running){
                if (!timer.isActive())
                    timer.start(datalist[2].toInt()*1000);
                emit SendCommand(sCommand);
                if (timer.remainingTime() == 0) running = false;
            }
            this->Data = "";
            this->Mode = NoModeSet;
            emit IsDone();
        }
        else if (this->Mode == SetController){
            if (this->Data.contains("enable")) this->ControllerPtr->OpenPorts();
            else if (this->Data.contains("disable")) this->ControllerPtr->ClosePorts();
            this->Data = "";
            this->Mode = NoModeSet;
            emit IsDone();
        }
    }
}

void HBCommandCenter::ParseConsoleCommand(QString data){
    this->Data = data.simplified();
    if (data.startsWith("walk")) this->Mode = EmitWalk;
    else if (this->Data.toLower().startsWith("controller")) this->Mode = SetController;
}
