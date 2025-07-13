#include "ConfigSetup.h"

Config config;

void Config::fromDoc(JsonDocument &doc)
{
    temp = doc[JK_TEMP] | 26;
    fan = doc[JK_FAN] | FAN::SPEED::AUTO;
    power = doc[JK_POWER] | HIGH;
    climateMode = doc[JK_CLIMATEMODE] | CLIMATE::MODE::AUTO;
    swingV = doc[JK_SWINGV] | SWING::MODE_V::AUTO;
    health = doc[JK_HEALTH] | LOW;
    quiet = doc[JK_QUIET] | LOW;
    turbo = doc[JK_TURBO] | LOW;
    disp = doc[JK_DISP] | HIGH;
}

void Config::toDoc(JsonDocument &doc)
{
    doc[JK_TEMP] = temp;
    doc[JK_FAN] = fan;
    doc[JK_POWER] = power;
    doc[JK_CLIMATEMODE] = climateMode;
    doc[JK_SWINGV] = swingV;
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

    JsonDocument doc;
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
    JsonDocument doc;
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
}
