#include "DatabaseHandler.hpp"

MessageHandler::Gateway::DatabaseHandler::DatabaseHandler(QString& _address, quint16& _port) : MqttInterface(_address, _port)
{
    /* Append all subscription topics to vector in parent class */
    this->topics->append("/edges/new_edge");
}

void MessageHandler::Gateway::DatabaseHandler::new_message(QMqttMessage _payload)
{
    /* Forward payload to virtual method of base class */
    MessageHandler::MqttInterface::new_message(_payload);
    
    if (_payload.topic().name() == "/edges/new_edge") { emit new_edge(_payload.payload());  }
    /* elseif all other topics here as well */
}

void MessageHandler::Gateway::DatabaseHandler::heartbeat_received()
{

}
