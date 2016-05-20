#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

class Spider : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Spider(QObject *parent = 0);

private:
    quint16 Mode;
    bool IsWalking;
    int Command;
    bool StandbyMsgSend;

    void run();
    void Walk(quint8 command);

signals:

public slots:
    void SetCommand(quint16 command);
    void SetMode(quint16 mode);
};

#endif // SPIDER_H
