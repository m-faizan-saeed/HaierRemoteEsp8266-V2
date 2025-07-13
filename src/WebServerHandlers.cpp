#include "WebServerHandlers.h"

AsyncWebServer server(80);

void setupWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello from ESP8266!"); });

  server.begin();
}