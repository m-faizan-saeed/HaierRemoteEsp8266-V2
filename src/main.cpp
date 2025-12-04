#include <Arduino.h>

#include "modules/wifi/wifi_manager.h"
#include "modules/webserver/web_server.h"
#include "modules/ir/ir_remote.h"
#include "modules/sensors/dht_sensor.h"
#include "config/config.h"

void setup()
{
  Serial.begin(115200);
  
  setupConfig();
  setupWiFi();
  setupWebServer();
  setupIR();
  // initDHT22(D4);  // GPIO2 (D4 on ESP8266)
  registerWebHandlers();
}

void loop()
{
  // Read DHT22 sensor periodically (every 2 seconds minimum)
  // readDHT22(2000);
}


// curl -X PUT  -H "Content-Type: application/json"  -d '{"temp":30,"quiet":false,"turbo":true,"fan":0,"mode":2,"swingV":4,"health":true}'  http://192.168.1.225/state