#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "WiFiManagerSetup.h"

void setupWiFi()
{

  Serial.println("In setupWiFi");
  WiFiManager wm;
  wm.setConnectTimeout(10);
  if (!wm.autoConnect("ESP8266_AP", "12345678"))
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
  WiFi.disconnect(false, true);
  delay(2000);
  ESP.reset();
}