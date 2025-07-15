#include "WebServerHandlers.h"
#include "WiFiManagerSetup.h"
#include "ConfigSetup.h"
#include "IrRemoteSetup.h"

ESP8266WebServer server(80);

void setupWebServer()
{
      server.on("/", HTTP_GET, []()
                { server.send(200, "text/plain", "Hello from ESP8266!"); });

      server.on("/resetWifi", HTTP_GET, []()
                {
          resetWiFi();
          server.send(200, "text/plain", "Reset Wifi"); });

      //       AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/state", [](AsyncWebServerRequest *request, JsonVariant &json)
      //                                                                              {
      //             Serial.println("/State start");
      //             config.loadFromJsonVariant(json);
      //             // config.saveConfig();
      //             irRequested = true;
      //             AsyncResponseStream *response = request->beginResponseStream("application/json");
      //             JsonDocument doc = config.asJson();
      //             serializeJson(doc,*response);
      //             request->send(response);
      // #ifdef DEBUG
      //             serializeJson(doc,Serial);
      // #endif
      //             Serial.println("/State done"); });

      //       handler->setMethod(HTTP_PUT);
      //       server.addHandler(handler);

      server.on("/state", HTTP_PUT, []()
                {
                      DynamicJsonDocument root(1024);
                      DeserializationError error = deserializeJson(root, server.arg("plain"));
                      if(error){
                        return server.send(400, "text/plain", error.c_str());
                      }
                      JsonVariant jVariant = root.as<JsonVariant>();
                      config.loadFromJsonVariant(jVariant);
                      irRequested = true;
                      JsonDocument doc = config.asJson();
                      server.setContentLength(CONTENT_LENGTH_UNKNOWN); // Streamed length
                        server.send(200, "application/json", "");
                        serializeJson(doc, server.client());
                        server.client().stop(); });

      server.on("/saveConfig", HTTP_GET, []()
                { server.send(200, "text/plain", config.saveConfig() ? "Config Saved" : "Unable to save Config"); });

      server.serveStatic("/fs", FILESYSTEM, "/");

      server.begin();
}