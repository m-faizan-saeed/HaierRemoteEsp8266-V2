#include "config.h"

Config config;

void Config::fromDoc(JsonDocument &doc)
{
    temp = doc[JK_TEMP] | 26;
    fan = static_cast<FAN::SPEED>(doc[JK_FAN] | static_cast<uint8_t>(FAN::SPEED::AUTO));
    power = doc[JK_POWER] | true;
    climateMode = static_cast<CLIMATE::MODE>(doc[JK_CLIMATEMODE] | static_cast<uint8_t>(CLIMATE::MODE::AUTO));
    swingV = static_cast<SWING::MODE_V>(doc[JK_SWINGV] | static_cast<uint8_t>(SWING::MODE_V::AUTO));
    health = doc[JK_HEALTH] | false;
    quiet = doc[JK_QUIET] | false;
    turbo = doc[JK_TURBO] | false;
    disp = doc[JK_DISP] | true;
}

void Config::toDoc(JsonDocument &doc)
{
    doc[JK_TEMP] = temp;
    doc[JK_FAN] = static_cast<uint8_t>(fan);
    doc[JK_POWER] = power;
    doc[JK_CLIMATEMODE] = static_cast<uint8_t>(climateMode);
    doc[JK_SWINGV] = static_cast<uint8_t>(swingV);
    doc[JK_HEALTH] = health;
    doc[JK_QUIET] = quiet;
    doc[JK_TURBO] = turbo;
    doc[JK_DISP] = disp;
}

bool Config::loadConfig()
{
    File file = LittleFS.open("/config.json", "r");
    if (!file)
    {
        Serial.println("No config file found");
        return false;
    }

    // JsonDocument doc;
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error)
    {
        Serial.print("Failed to parse config: ");
        Serial.println(error.c_str());
        // return false;
    }

    fromDoc(doc);

    Serial.println("Config loaded");
    return true;
}

bool Config::saveConfig()
{
    // JsonDocument doc;
    StaticJsonDocument<256> doc;
    toDoc(doc);
    File file = LittleFS.open("/config.json", "w");
    if (!file)
    {
        Serial.println("Failed to open config file for writing");
        return false;
    }
    serializeJson(doc, file);
    file.close();
    Serial.println("Config Saved");
    return true;
}

void setupConfig()
{
    if (!FILESYSTEM.begin())
    {
        Serial.println("Failed to mount file system");
        return;
    }
    config.loadConfig();
}
