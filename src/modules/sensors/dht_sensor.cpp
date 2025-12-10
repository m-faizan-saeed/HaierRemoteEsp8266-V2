#include "dht_sensor.h"
#include <DHT.h>
#include <Arduino.h>

// DHT sensor instance
static DHT dht(D4, DHT22);  // GPIO2 (D4 on ESP8266)
static SensorReading currentReading = {0.0f, 0.0f, 0, false};
static uint32_t lastReadTime = 0;

void initDHT22()
{
    dht.begin();
    Serial.println("DHT22 sensor initialized");
}

void readDHT22(uint32_t interval_ms)
{
    uint32_t now = millis();
    
    // Only read if interval has passed
    if (now - lastReadTime < interval_ms) {
        return;
    }
    
    lastReadTime = now;
    
    // Read humidity first (slower sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    // Check if any reads failed
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        currentReading.isValid = false;
        return;
    }
    
    // Update cached reading
    currentReading.temperature = t;
    currentReading.humidity = h;
    currentReading.lastReadTime = now;
    currentReading.isValid = true;
    
    Serial.printf("Temperature: %.2f°C, Humidity: %.2f%%\n\r", t, h);
}

SensorReading getSensorData()
{
    return currentReading;
}

bool isSensorDataStale(uint32_t max_age_ms)
{
    if (!currentReading.isValid) {
        return true;
    }
    
    return (millis() - currentReading.lastReadTime) > max_age_ms;
}
