#include "gree_ac_adapter.h"

GreeACAdapter::GreeACAdapter(uint8_t irPin) : ac(irPin)
{
}

void GreeACAdapter::begin()
{
    ac.begin();
}

void GreeACAdapter::setPower(bool on)
{
    ac.setPower(on);
}

void GreeACAdapter::setTemp(uint8_t temp)
{
    ac.setTemp(temp);
}

void GreeACAdapter::setFan(FAN::SPEED speed)
{
    uint8_t greeFanSpeed = kGreeFanAuto;
    switch (speed)
    {
    case FAN::SLOW:
        greeFanSpeed = kGreeFanMin;
        break;
    case FAN::MEDIUM:
        greeFanSpeed = kGreeFanMed;
        break;
    case FAN::FAST:
        greeFanSpeed = kGreeFanMax;
        break;
    case FAN::AUTO:
        greeFanSpeed = kGreeFanAuto;
        break;
    }
    ac.setFan(greeFanSpeed);
}

void GreeACAdapter::setMode(CLIMATE::MODE mode)
{

    uint8_t greeClimateMode = kGreeAuto;
    switch (mode)
    {
    case CLIMATE::COOL:
        greeClimateMode = kGreeCool;
        break;
    case CLIMATE::DRY:
        greeClimateMode = kGreeDry;
        break;
    case CLIMATE::FAN:
        greeClimateMode = kGreeFan;
        break;
    case CLIMATE::HEAT:
        greeClimateMode = kGreeHeat;
        break;
    case CLIMATE::AUTO:
        greeClimateMode = kGreeAuto;
        break;
    }
    ac.setMode(greeClimateMode);
}

void GreeACAdapter::setSwingV(SWING::MODE_V mode)
{

    uint8_t greeVerticalSwingMode = kGreeSwingAuto;

    switch (mode)
    {
    case SWING::OFF:
        greeVerticalSwingMode = kGreeSwingLastPos;
        break;
    case SWING::TOP:
        greeVerticalSwingMode = kGreeSwingUp;
        break;
    case SWING::FRONT:
        greeVerticalSwingMode = kGreeSwingMiddleUp;
        break;
    case SWING::BOTTOM:
        greeVerticalSwingMode = kGreeSwingMiddleDown;
        break;
    case SWING::DOWN:
        greeVerticalSwingMode = kGreeSwingDown;
        break;
    case SWING::AUTO:
        greeVerticalSwingMode = kGreeSwingAuto;
        break;
    }
    ac.setSwingVertical(true, greeVerticalSwingMode);
}

void GreeACAdapter::setHealth(bool on)
{
    // ac.setHealth(on); Not implemented in GreeAC
}

void GreeACAdapter::setTurbo(bool on)
{
    ac.setTurbo(on);
}

void GreeACAdapter::setQuiet(bool on)
{
    setFan(FAN::SPEED::SLOW);
}

void GreeACAdapter::setDisplay(bool on)
{
    // gree AC176 may not have display toggle; implement if available
    (void)on; // Suppress unused parameter warning
}

void GreeACAdapter::send()
{
    ac.send();
}

void GreeACAdapter::printState()
{
    Serial.println("A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
}
