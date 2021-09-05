#include <QtCore>
#include <QCoreApplication>
#include <QObject>

#include "include/MqttInterface.hpp"
#include "include/EdgeHandler.hpp"
#include "include/DatabaseHandler.hpp"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    /* Configure broker (server) */
    QString broker_addr = "127.0.0.1";
    quint16 broker_port = 1883;

    /* Initialize a unique pointer to EdgeHandler */
    QScopedPointer<MessageHandler::Gateway::EdgeHandler> edge_handler = QScopedPointer<MessageHandler::Gateway::EdgeHandler>(
        new MessageHandler::Gateway::EdgeHandler(broker_addr, broker_port)
    );

    /* Initialize a unique pointer to DatabaseHandler */
    QScopedPointer<MessageHandler::Gateway::DatabaseHandler> database_handler = QScopedPointer<MessageHandler::Gateway::DatabaseHandler>(
        new MessageHandler::Gateway::DatabaseHandler(broker_addr, broker_port)
    );

    a.exec();
}
