#include "hbserialbluetooth.h"

HBSerialBluetooth::HBSerialBluetooth()
{
    Serial = new QSerialPort();
    connect(Serial, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
<<<<<<< HEAD
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
=======
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
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08
    }
}

void HBSerialBluetooth::ProcessSerialData(){
    QByteArray data = Serial->readAll();
<<<<<<< HEAD
    int lastIndex = data.length()-1;
    QByteRef lastData = data[lastIndex];
    //qDebug() << data;
    switch(lastData){
    case 0x00:
        break;
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
        if (data.length() > 1)
            qDebug().nospace().noquote() << "Unsupported data type from bluetooth: 0x" << data[lastIndex-1] << data[lastIndex];
        break;
    }
}

HBSerialBluetooth::~HBSerialBluetooth(){
    this->Rfcomm.kill();
}


void HBSerialBluetooth::ClosePorts(){
    this->Serial->close();
=======
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
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08
}
