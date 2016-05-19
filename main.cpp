#include <QCoreApplication>
#include <hbwebserver.h>
#include <hbserialbluetooth.h>
#include <spider.h>
#include <heisenberg.conf>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HBSerialBluetooth *sbt = new HBSerialBluetooth();
    HBWebServer *server = new HBWebServer(WEBSOCKETSERVER_PORT);
    Spider *spider = new Spider();
    QObject::connect(sbt, SIGNAL(Walk(quint8)), spider, SLOT(Walk(quint8)));
    QObject::connect(server, &HBWebServer::closed, &a, &QCoreApplication::quit);
    QObject::connect(&a, SIGNAL(aboutToQuit()), sbt, SLOT(ClosePorts()));

    return a.exec();
}

