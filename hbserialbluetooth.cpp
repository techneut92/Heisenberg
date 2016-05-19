#include "hbserialbluetooth.h"

HBSerialBluetooth::HBSerialBluetooth()
{
    Serial = new QSerialPort();
    //this->connectBluetooth();
    //QThread::sleep(10);
    connect(Serial, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
    Serial->setPortName(SERIALPORT);
    Serial->setBaudRate(BAUDRATE);
    Serial->setDataBits(QSerialPort::Data8);
    Serial->setParity(QSerialPort::NoParity);
    Serial->setStopBits(QSerialPort::OneStop);
    Serial->setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "Serial port set to: " << SERIALPORT << "baudrate: " << BAUDRATE;
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
        }
        if (error == "Unknown error") qDebug() << "Bluetooth connected to" << Serial->portName();
        else if (error == "Permission error while locking the device")
            qCritical() << "Run program as root";
        else qDebug() << error;
    }
}

void HBSerialBluetooth::ProcessSerialData(){
    QByteArray data = Serial->readAll();
    qDebug() << data;
    if(data[data.length()-1] == 0)
    {
        this->Memory.append( data );
        this->processMemory();
        this->Memory = 0;
    }else this->Memory.append( data );
}

HBSerialBluetooth::~HBSerialBluetooth(){
    this->Rfcomm.kill();
}

void HBSerialBluetooth::processMemory(){
    QList<QByteArray> data = this->Memory.split(0x00);
    qDebug() << data;
    foreach(QByteArray d, data){
        if (!d.isEmpty()){
            switch(d[0]){
            case 0x01:
                emit this->Walk(1); // forward
                break;
            case 0x02:
                emit this->Walk(2); // backward
                break;
            case 0x03:
                emit this->Walk(3); // right
                break;
            case 0x04:
                emit this->Walk(4); // left
                break;
            case 0x08:

                break;
            }
        }
    }
}

//void HBSerialBluetooth::connectBluetooth(){
    //QString command = "rfcomm connect " + QString(CHANNEL) + " " + QString(BTMACADDR);
    //this->Rfcomm.start(command);
    //qDebug() << "Taking 10 seconds to connect with bluetooth device mac: " << BTMACADDR << "....";
//}

//void HBSerialBluetooth::killBluetooth(){
    //this->Rfcomm.kill();
    //this->Rfcomm.start("rfcomm release " + QString(CHANNEL));
//}

void HBSerialBluetooth::ClosePorts(){
    this->Serial->close();
}
