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

void Spider::SetMode(quint16 mode){
    this->Mode = mode;
}

void Spider::run(){
    while(true){
        //qDebug() << "Spider is doing its thing 8) command: " << this->Command;
        switch(this->Command){
        case 1:
            emit this->Walk(1);
            break;
        case 2:
            emit this->Walk(2);
            break;
        case 3:
            emit this->Walk(3);
            break;
        case 4:
            emit this->Walk(4);
            break;
        case 0:
            emit Stand();
            break;
        }
        this->Command = 0;
        QThread::usleep(200);
    }
}
