# message-handler
MQTT-based message handler to ensure connectivity between all endpoints

## Topics
### Repositories:
```
/virushash/{hash_key} - Repository for all virus hashes
/products/{product_id} - Repository for all products
/vendors/{vendor_id} - Repository for all vendors
```

### Actions:
```
/edges/new_edge - Register a new edge computer
/edges/{id}/heartbeat - Send a heartbeat signal to broker
```
