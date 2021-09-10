#include "MmiHandler.hpp"

MessageHandler::Gateway::MmiHandler::MmiHandler(QString& _address, quint16& _port) : MqttInterface(_address, _port)
{
    /* Append all subscription topics to vector in parent class */
    this->topics->append("/edges/#");
}

void MessageHandler::Gateway::MmiHandler::new_message(QMqttMessage _payload)
{
    /* Forward payload to virtual method of base class */
    MessageHandler::MqttInterface::new_message(_payload);
    qInfo() << "Virtual hello from MmiHandler";
}

void MessageHandler::Gateway::MmiHandler::heartbeat_received()
{

}

void MessageHandler::Gateway::MmiHandler::get_all_edges()
{
    
}
