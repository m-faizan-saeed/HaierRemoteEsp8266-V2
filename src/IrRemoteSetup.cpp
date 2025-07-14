#include "IrRemoteSetup.h"
#include "ConfigSetup.h"

IRHaierAC176 ac(4);
// IRGreeAC ac(4);

// #define FAN_SPEED_LOW kHaierAcFanLow
// #define AC_CLIMATE_COOL kHaierAcCool
// #define AC_CLIMATE_DRY kHaierAcDry
// #define AC_CLIMATE_FAN kHaierAcFan
// #define AC_CLIMATE_HEAT kHaierAcHeat
// #define AC_CLIMATE_AUTO kHaierAcAuto

#define AC_FAN_LOW kGreeFanMin
#define AC_FAN_MED kGreeFanMed
#define AC_FAN_HIG kGreeFanMax
#define AC_FAN_AUTO kGreeFanAuto

#define AC_CLIMATE_COOL kGreeCool
#define AC_CLIMATE_DRY kGreeDry
#define AC_CLIMATE_FAN kGreeFan
#define AC_CLIMATE_HEAT kGreeHeat
#define AC_CLIMATE_AUTO kGreeAuto

bool irRequested = false;

void printIrState()
{
    Serial.println("A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
}

void setupIR()
{
    ac.begin();
    Serial.println("Default state of the remote.");
    printIrState();
    Serial.println("Setting initial state for A/C.");
    ac.off();
    ac.setFan(AC_FAN_LOW);
    ac.setMode(AC_CLIMATE_COOL);
    ac.setTemp(25);
    ac.setSwing(false);
    printIrState();
}

uint8_t mapClimateMode(CLIMATE::MODE &mode)
{
    switch (mode)
    {
    case CLIMATE::COOL:
        return AC_CLIMATE_COOL;
    case CLIMATE::DRY:
        return AC_CLIMATE_DRY;
    case CLIMATE::FAN:
        return AC_CLIMATE_FAN;
    case CLIMATE::HEAT:
        return AC_CLIMATE_HEAT;
    case CLIMATE::AUTO:
    default:
        return AC_CLIMATE_AUTO;
    }
}

uint8_t mapFanSpeed(FAN::SPEED &mode)
{
    switch (mode)
    {
    case FAN::SLOW:
        return AC_FAN_LOW;
    case FAN::MEDIUM:
        return AC_FAN_MED;
    case FAN::FAST:
        return AC_FAN_HIG;
    case FAN::AUTO:
    default:
        return AC_FAN_AUTO;
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

void sendIR()
{
    setRemoteState();
    ac.send();
    printIrState();
}

inline void handleIrLoop()
{
    if (irRequested)
    {
        sendIR();
        irRequested = false;
    }
}