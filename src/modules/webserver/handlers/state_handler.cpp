#include "state_handler.h"
#include <ArduinoJson.h>
#include "config/config.h"
#include "modules/ir/ir_remote.h"

void handleStateRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    // Convert received data to string
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
    config.saveConfig();  // Persist the configuration
    sendIR();  // Send IR command with new state

    request->send(200, "application/json", "{\"status\":\"ok\"}");
}
