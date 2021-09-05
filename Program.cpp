#include <QtCore>
#include <QCoreApplication>
#include <QObject>

#include "include/MqttHandler.hpp"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    /* Configure broker (server) */
    QString broker_addr = "127.0.0.1";
    quint16 broker_port = 1883;

    /* Initialize a unique pointer to MQTT handler*/
    QScopedPointer<Mqtt::Handler> mqtt_handler = QScopedPointer<Mqtt::Handler>(new Mqtt::Handler(broker_addr, broker_port));

    /* Establish connection with MQTT broker */
    mqtt_handler->connect();

    a.exec();
}
