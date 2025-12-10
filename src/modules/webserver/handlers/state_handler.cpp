#include "state_handler.h"
#include <ArduinoJson.h>
#include "config/config.h"
#include "modules/ir/ir_remote.h"

void handleStatePutRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    static String body;

    if (index == 0)
    {
        body = "";
        body.reserve(total); // prevent fragmentation
    }

    body.concat((const char *)data, len);

    // If not finished receiving chunks, wait
    if (index + len < total)
        return;

    Serial.println("Received JSON:");
    Serial.println(body);

    // Allocate document with correct size
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, body);

    if (error)
    {
        Serial.print("JSON parse failed: ");
        Serial.println(error.c_str());
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    config.fromDoc(doc);
    // config.saveConfig();
    sendIR();

    request->send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleStateGetRequest(AsyncWebServerRequest *request)
{
    StaticJsonDocument<256> doc;
    config.toDoc(doc);

    String response;
    serializeJson(doc, response);

#ifdef DEBUG
    Serial.println("Sending JSON:");
    Serial.println(response);
#endif
    request->send(200, "application/json", response);
}