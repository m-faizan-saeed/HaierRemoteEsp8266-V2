#include "ConfigSetup.h"

Config::Config()
{
    if (!FILESYSTEM.begin())
    {
        Serial.println("Failed to mount file system");
        return;
    }
    loadConfig();
}

Config::~Config()
{
    FILESYSTEM.end();
}

void Config::loadFromJsonVariant(JsonVariant &json)
{
    temp = json[JK_TEMP] | 26;
    fan = json[JK_FAN] | FAN::SPEED::AUTO;
    power = json[JK_POWER] | HIGH;
    climateMode = json[JK_CLIMATEMODE] | CLIMATE::MODE::AUTO;
    swingV = json[JK_SWINGV] | SWING::MODE_V::AUTO;
    health = json[JK_HEALTH] | LOW;
    quiet = json[JK_QUIET] | LOW;
    turbo = json[JK_TURBO] | LOW;
    toggleDisp = json[JK_DISP] | LOW;
}

void Config::writeToJsonVariant(JsonVariant &json)
{
    json[JK_TEMP] = temp;
    json[JK_FAN] = fan;
    json[JK_POWER] = power;
    json[JK_CLIMATEMODE] = climateMode;
    json[JK_SWINGV] = swingV;
    json[JK_HEALTH] = health;
    json[JK_QUIET] = quiet;
    json[JK_TURBO] = turbo;
    json[JK_DISP] = toggleDisp;
}

JsonDocument Config::asJson()
{
    JsonDocument doc;
    JsonVariant variant = doc.as<JsonVariant>();
    writeToJsonVariant(variant);
    return doc;
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
    JsonVariant config = doc.as<JsonVariant>();
    loadFromJsonVariant(config);
    Serial.println("Config loaded");
    serializeJson(doc, Serial);
    return true;
}

bool Config::saveConfig()
{
    JsonDocument doc = asJson();

    File file = LittleFS.open("/config.json", "w");
    if (!file)
    {
        Serial.println("Failed to open config file for writing");
        return false;
    }
    serializeJson(doc, file);
    file.close();
    Serial.println("Config Saved");
    serializeJson(doc, Serial);
    return true;
}

Config config;