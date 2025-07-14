#include <ESP8266WiFi.h>
#include <WiFiManager.h>

#include "WiFiManagerSetup.h"


WiFiManager wifiManager;

void setupWiFi()
{
  Serial.println("In setupWiFi");
  wifiManager.setConnectTimeout(10);
  if (!wifiManager.autoConnect("ESP8266_AP", "12345678"))
  {
    Serial.println("Failed to connect. Running AP mode.");
  }
  else
  {
    Serial.println("Connected: " + WiFi.localIP().toString());
  }
}

void resetWiFi()
{
  // WiFi.disconnect(false, true);
  wifiManager.resetSettings();
  delay(2000);
  ESP.reset();
}