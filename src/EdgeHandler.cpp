#include "EdgeHandler.hpp"

MessageHandler::Gateway::EdgeHandler::EdgeHandler(QString& _address, quint16& _port) : MqttInterface(_address, _port)
{
    /* Append all subscription topics to vector in parent class */
    this->topics->append("/virushash/#");

    /* Bind signals and slots */
    QObject::connect(this, &EdgeHandler::register_new_edge, this, &EdgeHandler::on_new_edge);
}

/**
 * @brief Register a new edge computer
 * @param mac_address
 *
 * This method is called by new edge computers on the network
 */
void MessageHandler::Gateway::EdgeHandler::on_new_edge(QString& mac_address)
{
    QJsonObject payload;
    payload["MACAddress"] = mac_address;
    payload["IsOnline"] = true;
    payload["LastHeartbeat"] = QDateTime::currentDateTime().toString();

    QString topic = "/edges/new_edge";
    this->publish(topic, payload);
}

void MessageHandler::Gateway::EdgeHandler::heartbeat_received()
{

}

void MessageHandler::Gateway::EdgeHandler::new_message(QMqttMessage _payload)
{
    /* Forward payload to virtual method of base class */
    MessageHandler::MqttInterface::new_message(_payload);
    qInfo() << "Virtual hello from EdgeHandler";
}

void MessageHandler::Gateway::EdgeHandler::broker_connected()
{   
    /* Call virtual method of base class */
    MessageHandler::MqttInterface::broker_connected();

    /* Register edge computer within the network */
    QString mac_address = "Heisann";
    emit register_new_edge(mac_address);
    qInfo() << "Edge" << mac_address << "has been registered on the network";
}
