#include "spider.h"

Spider::Spider(QObject *parent) : QObject(parent) , QRunnable()
{
    this->Mode = 1;
    this->IsWalking = false;
    this->Command=0;
    this->StandbyMsgSend = false;
}

void Spider::SetCommand(quint16 command){
    this->Command = command;
}

void Spider::Walk(quint8 command){
    if (!this->IsWalking){
        this->IsWalking = true;
        QString debug;
        switch(command){
        case 1:
            debug = "Walking forward";
            break;
        case 2:
            debug = "Walking backward";
            break;
        case 3:
            debug = "Turning left";
            break;
        case 4:
            debug = "Turning right";
            break;
        }
        qDebug().noquote().nospace() << "Walk invoked - " << debug;
        QThread::sleep(2);
        this->IsWalking = false;
    }
}
void Spider::SetMode(quint16 mode){
    this->Mode = mode;
}

void Spider::run(){
    while(true){
        //qDebug() << "Spider is doing its thing 8) command: " << this->Command;
        switch(this->Command){
        case 1:
            this->StandbyMsgSend = false;
            this->Walk(1);
            break;
        case 2:
            this->StandbyMsgSend = false;
            this->Walk(2);
            break;
        case 3:
            this->StandbyMsgSend = false;
            this->Walk(3);
            break;
        case 4:
            this->StandbyMsgSend = false;
            this->Walk(4);
            break;
        case 0:
            if (!this->StandbyMsgSend) {
                qDebug() << "Spider is waiting for your orders, Sir";
                this->StandbyMsgSend = true;
            }
        }
        this->Command = 0;
        QThread::sleep(1);
    }
}
