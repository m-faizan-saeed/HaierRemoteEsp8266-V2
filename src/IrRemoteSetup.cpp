#include "IrRemoteSetup.h"
#include "ConfigSetup.h"

// IRHaierAC176 ac(4);

// #define AC_FAN_LOW kHaierAcFanLow
// #define AC_FAN_MED kHaierAcFanMed
// #define AC_FAN_HIG kHaierAcFanHigh
// #define AC_FAN_AUTO kHaierAcFanAuto

// #define FAN_SPEED_LOW kHaierAcFanLow
// #define AC_CLIMATE_COOL kHaierAcCool
// #define AC_CLIMATE_DRY kHaierAcDry
// #define AC_CLIMATE_FAN kHaierAcFan
// #define AC_CLIMATE_HEAT kHaierAcHeat
// #define AC_CLIMATE_AUTO kHaierAcAuto

// #define AC_SWING_V_AUTO kHaierAc160SwingVAuto
// #define AC_SWING_V_OFF kHaierAc160SwingVOff
// #define AC_SWING_V_TOP kHaierAc160SwingVTop
// #define AC_SWING_V_FRONT kHaierAc160SwingVMiddle
// #define AC_SWING_V_BOTTOM kHaierAc160SwingVLow
// #define AC_SWING_V_DOWN kHaierAc160SwingVLowest

IRGreeAC ac(4, gree_ac_remote_model_t::YAW1F);

#define AC_FAN_LOW kGreeFanMin
#define AC_FAN_MED kGreeFanMed
#define AC_FAN_HIG kGreeFanMax
#define AC_FAN_AUTO kGreeFanAuto

#define AC_CLIMATE_COOL kGreeCool
#define AC_CLIMATE_DRY kGreeDry
#define AC_CLIMATE_FAN kGreeFan
#define AC_CLIMATE_HEAT kGreeHeat
#define AC_CLIMATE_AUTO kGreeAuto

#define AC_SWING_V_AUTO kGreeSwingAuto
#define AC_SWING_V_OFF kGreeSwingLastPos
#define AC_SWING_V_TOP kGreeSwingUp
#define AC_SWING_V_FRONT kGreeSwingMiddleUp
#define AC_SWING_V_BOTTOM kGreeSwingMiddleDown
#define AC_SWING_V_DOWN kGreeSwingDown

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
    // ac.setSwing(false);
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
        return AC_SWING_V_OFF;
    case SWING::TOP:
        return AC_SWING_V_TOP;
    case SWING::FRONT:
        return AC_SWING_V_FRONT;
    case SWING::BOTTOM:
        return AC_SWING_V_BOTTOM;
    case SWING::DOWN:
        return AC_SWING_V_DOWN;
    case SWING::AUTO:
    default:
        return AC_SWING_V_AUTO;
    }
}

void setRemoteState()
{
    ac.setPower(config.power);
    ac.setTemp(config.temp);
    ac.setMode(mapClimateMode(config.climateMode));
    ac.setFan(mapFanSpeed(config.fan));
    // ac.setSwingV(mapSwingModeVertical(config.swingV));
    ac.setSwingVertical(true, mapSwingModeVertical(config.swingV));
    // ac.setHealth(config.health);
    ac.setTurbo(config.turbo);
    // ac.setQuiet(config.quiet);
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

void handleIR()
{
    if (irRequested)
    {
        sendIR();
        irRequested = false;
    }
}