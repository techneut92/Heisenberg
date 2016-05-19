#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QDebug>

class Spider : public QObject
{
    Q_OBJECT
public:
    explicit Spider(QObject *parent = 0);

private:
    quint16 Mode = 1;
    bool IsWalking = false;

signals:

public slots:
    void Walk(quint8 command);
    void SetMode(quint16 mode);
};

#endif // SPIDER_H
