#ifndef HBSERIALBLUETOOTH_H
#define HBSERIALBLUETOOTH_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QDebug>
#include "heisenberg.conf"
#include <QProcess>
#include <QThread>
#include <QTextStream>

class HBSerialBluetooth : public QObject
{
    Q_OBJECT
public:
    explicit HBSerialBluetooth();
    ~HBSerialBluetooth();
    //void connectBluetooth();

private:
    QSerialPort *Serial;
    QProcess Rfcomm;

signals:
    void SendCommand(quint16 command);

public slots:
    void ProcessSerialData();
    //void killBluetooth();
    void ClosePorts();

};

#endif // HBSERIALBLUETOOTH_H
