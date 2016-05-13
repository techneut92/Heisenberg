#include "hbserialbluetooth.h"

HBSerialBluetooth::HBSerialBluetooth()
{
    Serial = new QSerialPort();
    connect(Serial, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
    Serial->setPortName("/dev/rfcomm0");
    Serial->setBaudRate(QSerialPort::Baud9600);
    //Serial->setDataBits(QSerialPort::Data8);
    //Serial->setParity();
    //Serial->setStopBits(p.stopBits);
    //Serial->setFlowControl(p.flowControl);
    if (Serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to" << Serial->portName();
    } else {
        qDebug() << Serial->errorString();
    }
}

void HBSerialBluetooth::ProcessSerialData(){
    QByteArray data = Serial->readAll();
    if(data[data.length()-1] == 0x00)
    {
        this->Memory.append( data );
        this->processMemory();
        this->Memory = 0;
    }else this->Memory.append( data );
}

HBSerialBluetooth::~HBSerialBluetooth(){

}

void HBSerialBluetooth::processMemory(){
    QList<QByteArray> data = this->Memory.split(0x00);
    foreach(QByteArray d, data){
        if (!d.isEmpty())
        qDebug() << d.toHex();
    }
}
