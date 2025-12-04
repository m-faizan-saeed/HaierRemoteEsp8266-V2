#include <cstdint>
#ifndef CONFIG_H
#define CONFIG_H

// Setup File Systems
#if defined(ESP8266)
#include <LittleFS.h>
#else
#include <SPIFFS.h>
#endif

#ifndef FILESYSTEM
// Set the default filesystem if none was specified.
#ifdef ESP8266
#define FILESYSTEM LittleFS
#else
#define FILESYSTEM SPIFFS
#endif // defined(ESP8266)
#endif // FILESYSTEM

#if (FILESYSTEM == LittleFS)
#define FILESYSTEMSTR "LittleFS"
#else
#define FILESYSTEMSTR "SPIFFS"
#endif

#include <ArduinoJson.h>

#define JK_TEMP "temp"
#define JK_FAN "fan"
#define JK_POWER "power"
#define JK_CLIMATEMODE "mode"
#define JK_SWINGV "swingV"
#define JK_HEALTH "health"
#define JK_QUIET "quiet"
#define JK_TURBO "turbo"
#define JK_DISP "disp"


#include "types/config_types.h"

void setupConfig();

class Config
{
public:
    uint8_t temp;
    FAN::SPEED fan;
    bool power;
    CLIMATE::MODE climateMode;
    SWING::MODE_V swingV;
    bool health;
    bool quiet;
    bool turbo;
    bool disp;

    bool loadConfig();
    bool saveConfig();

    void fromDoc(JsonDocument &doc);
    void toDoc(JsonDocument &doc);
};

extern Config config;

#endif