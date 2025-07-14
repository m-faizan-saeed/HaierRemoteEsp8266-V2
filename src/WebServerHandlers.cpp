#include "WebServerHandlers.h"
#include "WiFiManagerSetup.h"
#include "ConfigSetup.h"
#include "IrRemoteSetup.h"

AsyncWebServer server(80);

void setupWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello from ESP8266!"); });

  server.on("/resetWifi", HTTP_GET, [&](AsyncWebServerRequest *request)
            {
    resetWiFi();
    request->send(200, "text/plain", "Reset Wifi"); });

  AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/state", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                                         {                                                                  
      Serial.println("/State start");
      config.loadFromJsonVariant(json);
      // sendIR();
      irRequested = true;
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      serializeJson(config.asJson(),*response);
      request->send(response); 
      Serial.println("/State done"); });
  handler->setMethod(HTTP_PUT);
  server.addHandler(handler);

  server.on("/saveConfig", HTTP_GET, [&](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", config.saveConfig() ? "Config Saved" : "Unable to save Config"); });

  server.serveStatic("/fs", FILESYSTEM, "/");

  server.begin();
}