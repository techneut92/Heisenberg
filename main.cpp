#include <QCoreApplication>
#include <hbwebserver.h>
#include <hbserialbluetooth.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HBSerialBluetooth *sbt = new HBSerialBluetooth();
    HBWebServer *server = new HBWebServer(13337);
    QObject::connect(server, &HBWebServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}

