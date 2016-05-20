#include "hbserialbluetooth.h"

HBSerialBluetooth::HBSerialBluetooth()
{
    Serial = new QSerialPort();
    //this->connectBluetooth();
    //QThread::sleep(10);
    connect(Serial, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
    Serial->setPortName(SERIALPORT);
    //Serial->setDataBits(QSerialPort::Data8);
    //Serial->setParity(QSerialPort::NoParity);
    //Serial->setStopBits(QSerialPort::OneStop);
    //Serial->setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "Serial port set to: " << SERIALPORT << "baudrate: " << Serial->baudRate();
    if (Serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to" << Serial->portName();
        Serial->clear();
    } else {
        QString error = Serial->errorString();
        while(error == "No such file or directory") {
            Serial->open(QIODevice::ReadWrite);
            QThread::sleep(10);
            qDebug() << "Attempting serial bluetooth connection.";
            error = Serial->errorString();
        }while(error == "Permission error while locking the device"){
            qCritical() << "Permission error while locking the device: Are you running program as root?";
            qCritical() << "Reattempting connection every 10 seconds....";
            Serial->open(QIODevice::ReadWrite);
            QThread::sleep(10);
            error = Serial->errorString();
        }
        if (error == "Unknown error") qDebug() << "Bluetooth connected to" << Serial->portName();

        else qDebug() << error;
    }
}

void HBSerialBluetooth::ProcessSerialData(){
    QByteArray data = Serial->readAll();
    int lastIndex = data.length()-1;
    QByteRef lastData = data[lastIndex];
    //qDebug() << lastData;
    switch(lastData){
    case 0x01:
        emit this->SendCommand(1); // forward
        break;
    case 0x02:
        emit this->SendCommand(2); // backward
        break;
    case 0x03:
        emit this->SendCommand(3); // right
        break;
    case 0x04:
        emit this->SendCommand(4); // left
        break;
    case 0x08:

        break;
    default:
        data = data.toHex();
        qDebug().nospace().noquote() << "Unsupported data type from bluetooth: 0x" << data[lastIndex-1] << data[lastIndex];
        break;
    }
}

HBSerialBluetooth::~HBSerialBluetooth(){
    this->Rfcomm.kill();
}


void HBSerialBluetooth::ClosePorts(){
    this->Serial->close();
}
