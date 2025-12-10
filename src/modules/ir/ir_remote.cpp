#include "ir_remote.h"
#include "ir_mapper.h"
#include "config/config.h"

IRHaierAC176 ac(D2); // GPIO4 (D2 on ESP8266)

void printState()
{
    Serial.println("A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
}

void setupIR()
{
    ac.begin();
    Serial.println("Default state of the remote.");
    printState();
    Serial.println("Setting initial state for A/C.");
    ac.off();
    ac.setFan(kHaierAcFanLow);
    ac.setMode(kHaierAcCool);
    ac.setTemp(25);
    ac.setSwing(false);
    printState();
}

void setRemoteState()
{
    ac.setPower(config.power);
    ac.setTemp(config.temp);
    ac.setMode(mapClimateMode(config.climateMode));
    ac.setFan(mapFanSpeed(config.fan));
    ac.setSwingV(mapSwingModeVertical(config.swingV));
    ac.setHealth(config.health);
    ac.setTurbo(config.turbo);
    ac.setQuiet(config.quiet);
    // if (config.toggleDisp)
    // {
    //     ac.toggleDisplayLED();
    // }
}

void sendIR()
{
    setRemoteState();
    ac.send();
}
