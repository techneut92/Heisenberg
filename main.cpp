#include <QCoreApplication>
#include <hbwebserver.h>
#include <hbserialbluetooth.h>
<<<<<<< HEAD
#include <spider.h>
#include <heisenberg.conf>
=======
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HBSerialBluetooth *sbt = new HBSerialBluetooth();
<<<<<<< HEAD
    HBWebServer *server = new HBWebServer(WEBSOCKETSERVER_PORT);
    Spider *spider = new Spider();

    spider->setAutoDelete(false);
    QThreadPool *threadPool = QThreadPool::globalInstance();
    threadPool->start(spider);

    QObject::connect(sbt, SIGNAL(SendCommand(quint16)), spider, SLOT(SetCommand(quint16)));
    QObject::connect(server, &HBWebServer::closed, &a, &QCoreApplication::quit);
    QObject::connect(&a, SIGNAL(aboutToQuit()), sbt, SLOT(ClosePorts()));
=======
    HBWebServer *server = new HBWebServer(13337);
    QObject::connect(server, &HBWebServer::closed, &a, &QCoreApplication::quit);
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08

    return a.exec();
}

