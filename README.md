# message-handler
MQTT-based message handler to ensure connectivity between all endpoints

## Topics
### Repositories:
```
/virushash/{hash_key} - Repository for all virus hashes
/products/{product_id} - Repository for all products
/vendors/{vendor_id} - Repository for all vendors
/edges/{mac_address} - Repository for all edge computers
```

### Actions:
```
/edges/new_edge - Register a new edge computer
/edges/get_all - Request a list of all connected edge computers
/edges/{id}/heartbeat - Send a heartbeat signal to broker
```

## Prerequisites
### QtMqtt:
```
git clone --branch 6.1.3 https://github.com/qt/qtmqtt
cd qtmqtt
qmake
sudo make
sudo make install
```
