#include "testmqtt.hpp"

TestMqtt::TestMqtt(QString &address, quint16 port, QList<QString> topicList) : m_address(address), m_port(port), m_topic_list(topicList)
{
    m_client = new QMqttClient();
    connect(m_client, &QMqttClient::stateChanged, this, &TestMqtt::clientStateChanged);
    connect(m_client, &QMqttClient::errorChanged, this, &TestMqtt::errorChanged);
    m_client->setHostname(m_address);
    m_client->setPort(m_port);
    m_client->connectToHost();
}

TestMqtt::~TestMqtt()
{
    qInfo() << "Ran deconstructor";
    m_client->disconnectFromHost();
    delete m_client;
}

void TestMqtt::clientStateChanged(QMqttClient::ClientState state)
{
    switch (state) {

    case QMqttClient::Disconnected:
        qDebug() << "Client Disconnected";
        break;
    case QMqttClient::Connecting:
        qDebug() << "Client Connecting";
        break;
    case QMqttClient::Connected:
        qDebug() << "Client Connected";
        if (!m_topic_list.isEmpty()){
            foreach(QString topic, m_topic_list){
                subscribe(topic);
            }
        }
        break;
    }
}

void TestMqtt::errorChanged()
{
    qInfo() << m_client->error();
}

void TestMqtt::subscribe(QString topic)
{
    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic);

    QMqttSubscription *sub = m_client->subscribe(topicFilter, 0);

    if (sub)
    {
        qDebug() << "subscribe on " + topic;
        connect(sub, &QMqttSubscription::messageReceived, this, &TestMqtt::onMessage);
    }
    else
        qDebug() << "Error subscription on "<< topic;
}

void TestMqtt::onMessage(QMqttMessage message)
{
    qDebug() << "mqtt message receive from topic : " <<  message.topic().name() << " payload : " <<
                message.payload();
}

void TestMqtt::publishData(QString &topic, QJsonObject &jsonData)
{
    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic);
    QJsonDocument data( jsonData );
    m_client->publish(topic, data.toJson());
}
