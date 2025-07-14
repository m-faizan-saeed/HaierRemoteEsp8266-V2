#include <Arduino.h>

#define DEBUG
// #include "DebugMacros.h"

#include "ConfigSetup.h"
#include "WiFiManagerSetup.h"
#include "IrRemoteSetup.h"
#include "WebServerHandlers.h"

void setup()
{
  Serial.begin(115200);

  setupWiFi();

  setupIR();

  setupWebServer();
}

void loop()
{
  // Serial.print('.');
  delay(10);
  handleIrLoop();
}
