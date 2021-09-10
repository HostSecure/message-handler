#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

#include "MqttInterface.hpp"

namespace MessageHandler::Gateway
{
    class DatabaseHandler : public MessageHandler::MqttInterface
    {
        Q_OBJECT

    public:
        explicit DatabaseHandler(QString&, quint16&);

    signals:
        void new_edge(QByteArray);

    public slots:
        void new_message(QMqttMessage) override;
        void heartbeat_received();
    };
}

#endif // DATABASEHANDLER_HPP
