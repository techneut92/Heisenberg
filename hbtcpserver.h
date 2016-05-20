#ifndef HBTCPSERVER_H
#define HBTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>

class HBTcpServer : public QTcpServer
{
public:
    Q_OBJECT
    explicit HBTcpServer();
    ~HBTcpServer();

private:


signals:


public slots:

};

#endif // HBTCPSERVER_H
