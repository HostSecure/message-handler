#include <iostream>
#include <string>
#include <QtCore>
#include <QCoreApplication>
#include <QObject>

//#include "include/MqttConnection.hpp"
#include "include/MqttHandler.hpp"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    /* Configure broker (server) */
    QString broker_addr = "127.0.0.1";
    quint16 broker_port = 1883;

    Mqtt::Handler* mqtt_handler = new Mqtt::Handler(broker_addr, broker_port);
    mqtt_handler->connect();

    a.exec();
}
