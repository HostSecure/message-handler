#ifndef MQTTHANDLER_HPP
#define MQTTHANDLER_HPP

#include <QtMqtt/QtMqtt>
#include <QMqttClient>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

namespace Mqtt
{
    struct BrokerConfig
    {
        QString address;    /* Server hostname */
        quint16 port;       /* Server port */
        quint16 heartbeat;  /* Ping response (seconds) */
    };

    class Handler : public QObject
    {
        Q_OBJECT

    public:
        explicit Handler(QString&, quint16&, QObject* parent = nullptr);
        void connect();
        void publish();
        void test();

        bool is_connected() const;
        QMqttClient::ClientState get_state() const;

    public slots:
        void broker_connected();
        void broker_disconnected();
        void state_changed();
        void client_error();
        void onMessage(QMqttMessage message);

    private:
        QSharedPointer<QMqttClient> mqtt_client;
        QSharedPointer<Mqtt::BrokerConfig> broker;
    };
}

#endif // MQTTHANDLER_HPP
