#include "IrRemoteSetup.h"
#include "ConfigSetup.h"

IRHaierAC176 ac(4);

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

uint8_t mapClimateMode(CLIMATE::MODE &mode)
{
    switch (mode)
    {
    case CLIMATE::COOL:
        return kHaierAcCool;
    case CLIMATE::DRY:
        return kHaierAcDry;
    case CLIMATE::FAN:
        return kHaierAcFan;
    case CLIMATE::HEAT:
        return kHaierAcHeat;
    case CLIMATE::AUTO:
    default:
        return kHaierAcAuto;
    }
}

uint8_t mapFanSpeed(FAN::SPEED &mode)
{
    switch (mode)
    {
    case FAN::SLOW:
        return kHaierAcFanLow;
    case FAN::MEDIUM:
        return kHaierAcFanMed;
    case FAN::FAST:
        return kHaierAcFanHigh;
    case FAN::AUTO:
    default:
        return kHaierAcFanAuto;
    }
}

uint8_t mapSwingModeVertical(SWING::MODE_V &mode)
{
    switch (mode)
    {
    case SWING::OFF:
        return kHaierAc160SwingVOff;
    case SWING::TOP:
        return kHaierAc160SwingVTop;
    case SWING::FRONT:
        return kHaierAc160SwingVMiddle;
    case SWING::BOTTOM:
        return kHaierAc160SwingVLow;
    case SWING::DOWN:
        return kHaierAc160SwingVLowest;
    case SWING::AUTO:
    default:
        return kHaierAc160SwingVAuto;
    }
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

void sendIr()
{
    setRemoteState();
    ac.send();
}
