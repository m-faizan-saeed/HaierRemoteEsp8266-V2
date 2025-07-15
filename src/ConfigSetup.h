#include <cstdint>
#ifndef CONFIG_SETUP_H
#define CONFIG_SETUP_H

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

namespace FAN
{
    enum SPEED : uint8_t
    {
        AUTO = 0,
        SLOW = 1,
        MEDIUM = 2,
        FAST = 3
    };
}

namespace CLIMATE
{
    enum MODE : uint8_t
    {
        AUTO = 0,
        COOL = 1,
        DRY = 2,
        HEAT = 3,
        FAN = 4
    };
}

namespace SWING
{
    enum MODE_V : uint8_t
    {
        AUTO = 0,
        OFF = 1,
        TOP = 2,
        FRONT = 3,
        BOTTOM = 4,
        DOWN = 5,
    };
}

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
    bool toggleDisp;

    Config();
    ~Config();

    bool loadConfig();
    bool saveConfig();

    void loadFromJsonVariant(JsonVariant &json);
    void writeToJsonVariant(JsonVariant &json);

    JsonDocument asJson();
};

extern Config config;

void setupConfig();

#endif