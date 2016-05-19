#include "spider.h"

Spider::Spider(QObject *parent) : QObject(parent)
{

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

        qDebug() << "Walk invoked - " << debug;
        this->IsWalking = false;
    }
}

void Spider::SetMode(quint16 mode){
    this->Mode = mode;
}
