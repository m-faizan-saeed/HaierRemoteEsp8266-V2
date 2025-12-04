#include "wifi_handler.h"
#include <ESP8266WiFi.h>

void handleResetWifi(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "Reset Wifi");
    
    // Delay to ensure response is sent
    delay(100);
    
    // Reset WiFi configuration and restart
    WiFi.disconnect(false, true);
    delay(2000);
    ESP.reset();
}
