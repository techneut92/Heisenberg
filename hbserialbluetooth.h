#ifndef HBSERIALBLUETOOTH_H
#define HBSERIALBLUETOOTH_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QDebug>
<<<<<<< HEAD
#include "heisenberg.conf"
#include <QProcess>
#include <QThread>
#include <QTextStream>
=======
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08

class HBSerialBluetooth : public QObject
{
    Q_OBJECT
public:
    explicit HBSerialBluetooth();
    ~HBSerialBluetooth();
<<<<<<< HEAD
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
=======

private:
    QSerialPort *Serial;
    QByteArray Memory;
    void processMemory();

signals:
    void Walk(char direction, int speed);

public slots:
    void ProcessSerialData();
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08

};

#endif // HBSERIALBLUETOOTH_H
