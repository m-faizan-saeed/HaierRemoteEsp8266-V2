#include "sensor_handler.h"
#include "../../sensors/dht_sensor.h"

void handleSensorDataRequest(AsyncWebServerRequest *request)
{
    // Minimal overhead response - no JSON parsing, direct streaming
    SensorReading data = getSensorData();
    
    if (!data.isValid) {
        request->send(503, "application/json", "{\"error\":\"No sensor data available\"}");
        return;
    }
    
    // Pre-allocated buffer for minimal overhead (avoids dynamic allocation in handler)
    char response[128];
    snprintf(response, sizeof(response),
             "{\"temperature\":%.2f,\"humidity\":%.2f,\"timestamp\":%u}",
             data.temperature,
             data.humidity,
             data.lastReadTime);
    
    request->send(200, "application/json", response);
}
