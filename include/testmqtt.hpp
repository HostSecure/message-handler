#ifndef TESTMQTT_HPP
#define TESTMQTT_HPP

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QDebug>

#define MQTT_ADDR "127.0.0.1"
#define MQTT_PORT 1883

class TestMqtt : public QObject
{
    Q_OBJECT

public:
    TestMqtt(QString &address, quint16 port, QList<QString> topicList);
    ~TestMqtt();

    QMqttClient* m_client;
    void publishData(QString &topic, QJsonObject &jsonData);

public slots:
    virtual void onMessage(QMqttMessage message);

private:
    void subscribe(QString topic);
    QString m_address;
    quint16 m_port;
    QList <QString> m_topic_list;

private slots:
    void clientStateChanged(QMqttClient::ClientState state);
    void errorChanged();

};

#endif // TESTMQTT_HPP
