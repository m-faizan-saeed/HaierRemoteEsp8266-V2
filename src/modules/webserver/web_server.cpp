#include "web_server.h"
#include "handlers/state_handler.h"
#include "handlers/wifi_handler.h"
#include "handlers/sensor_handler.h"

AsyncWebServer server(80);

void setupWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello from ESP8266!"); });

  server.begin();
}

void registerWebHandlers()
{
  server.on("/state", HTTP_PUT, [](AsyncWebServerRequest *request) {},
            NULL,
            handleStateRequest);

  server.on("/resetWifi", HTTP_GET, handleResetWifi);
  
  server.on("/sensor", HTTP_GET, handleSensorDataRequest);
}