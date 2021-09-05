#include "MqttHandler.hpp"

Mqtt::Handler::Handler(QString& _address, quint16& _port, QObject* parent) : QObject(parent)
{
    /* Initialize shared pointers */
    broker = QSharedPointer<Mqtt::BrokerConfig>(new Mqtt::BrokerConfig);
    mqtt_client = QSharedPointer<QMqttClient>(new QMqttClient);

    if (!broker.isNull())
    {
        /* Set broker configuration */
        broker->address = _address;
        broker->port = _port;
        broker->heartbeat = 60;
    }
    else qCritical() << "Broker is not initialized properly!";

    if (!mqtt_client.isNull())
    {
        /* Communication bindings */
        QObject::connect(mqtt_client.get(), &QMqttClient::connected, this, &Mqtt::Handler::broker_connected);
        QObject::connect(mqtt_client.get(), &QMqttClient::disconnected, this, &Mqtt::Handler::broker_disconnected);
        QObject::connect(mqtt_client.get(), &QMqttClient::stateChanged, this, &Mqtt::Handler::state_changed);
        QObject::connect(mqtt_client.get(), &QMqttClient::errorChanged, this, &Mqtt::Handler::client_error);

        qDebug() << "MQTT protocol version:" << mqtt_client->protocolVersion();
    }
    else qCritical() << "MqttClient is not initialized properly!";
}

void Mqtt::Handler::connect()
{
    mqtt_client->setHostname(broker->address);
    mqtt_client->setPort(broker->port);

    if (get_state() != QMqttClient::ClientState::Connected)
    {
        qInfo() << "Connecting to" << broker->address;
        mqtt_client->connectToHost();
    }
    else qInfo() << "Already connected to broker";
}

void Mqtt::Handler::publish()
{
    QString topic_name = "sira/halla";

    if (is_connected())
    {
        if (mqtt_client->publish(topic_name, "Heisann", true) == -1)
        {
            qInfo() << "Could not publish message";
        }
    }
    else qInfo() << "Not connected to broker!";

    /*
    auto subscribe = m_client->subscribe(topic_name);
    if (!subscribe)
    {
        qInfo() << "Could not subscribe. Is there a valid connection?";
        qInfo() << "Error:" << m_client->error();
    }
    */
}

QMqttClient::ClientState Mqtt::Handler::get_state() const
{
    return mqtt_client->state();
}

void Mqtt::Handler::test()
{

}

bool Mqtt::Handler::is_connected() const
{
    return (mqtt_client->state() == QMqttClient::ClientState::Connected);
}

void Mqtt::Handler::broker_connected()
{
    QString topic_name = "sira/halla";

    qInfo() << "Connected to" << broker->address << "on port" << broker->port;
    //this->publish();

    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic_name);

    QMqttSubscription *sub = mqtt_client->subscribe(topicFilter, 0);

    if (sub)
    {
        qDebug() << "subscribe on " + topic_name;
        QObject::connect(sub, &QMqttSubscription::messageReceived, this, &Mqtt::Handler::onMessage);
    }
    else
        qDebug() << "Error subscription on "<< topic_name;
}

void Mqtt::Handler::onMessage(QMqttMessage message)
{
    qDebug() << "mqtt message receive from topic : " <<  message.topic().name() << " payload : " << message.payload();
}

void Mqtt::Handler::broker_disconnected()
{
    qInfo() << "Disconnected from" << broker->address;
}

void Mqtt::Handler::state_changed()
{
    qDebug() << "State changed to" << get_state();
}

void Mqtt::Handler::client_error()
{
    qInfo() << "Error:" << mqtt_client->error();
}
