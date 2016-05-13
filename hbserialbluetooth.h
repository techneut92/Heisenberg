#ifndef HBSERIALBLUETOOTH_H
#define HBSERIALBLUETOOTH_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QDebug>

class HBSerialBluetooth : public QObject
{
    Q_OBJECT
public:
    explicit HBSerialBluetooth();
    ~HBSerialBluetooth();

private:
    QSerialPort *Serial;
    QByteArray Memory;
    void processMemory();

signals:
    void Walk(char direction, int speed);

public slots:
    void ProcessSerialData();

};

#endif // HBSERIALBLUETOOTH_H
