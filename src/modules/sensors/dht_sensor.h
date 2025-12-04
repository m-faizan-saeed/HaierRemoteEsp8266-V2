#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <cstdint>

// DHT22 sensor readings structure
struct SensorReading {
    float temperature;
    float humidity;
    uint32_t lastReadTime;  // Timestamp of last successful read
    bool isValid;           // Whether last reading is valid
};

// Initialize DHT22 on specified GPIO pin
void initDHT22(uint8_t pin);

// Read sensor data with caching (only reads every interval_ms)
void readDHT22(uint32_t interval_ms = 2000);

// Get current cached sensor data
SensorReading getSensorData();

// Check if sensor data is stale
bool isSensorDataStale(uint32_t max_age_ms = 5000);

#endif
