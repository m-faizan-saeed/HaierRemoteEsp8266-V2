#include <Arduino.h>

#include "WiFiManagerSetup.h"
#include "WebServerHandlers.h"
#include "IrRemoteSetup.h"
#include "ConfigSetup.h"

void resetWiFi();
void sendIr();

void setup()
{
  Serial.begin(115200);
  setupConfig();

  setupWiFi();
  setupWebServer();
  setupIR();

  server.on("/resetWifi", HTTP_GET, [&](AsyncWebServerRequest *request)
            {
    resetWiFi();
    request->send(200, "text/plain", "Reset Wifi"); });

  server.on("/state", HTTP_PUT, [](AsyncWebServerRequest *request) {},
            NULL, // No file upload handler
            [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
            {
      // Convert to string (or use directly from data)
      String jsonString = "";
      for (size_t i = 0; i < len; i++) {
        jsonString += (char)data[i];
      }

      Serial.println("Received JSON:");
      Serial.println(jsonString);

      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, jsonString);
      if (error) {
        Serial.print("JSON parse failed: ");
        Serial.println(error.c_str());
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
      }
      config.fromDoc(doc);
      sendIr();
      request->send(200, "application/json", "{\"status\":\"ok\"}"); });
}

void loop()
{
  // Serial.print('.');
}
