#include "haier_ac_adapter.h"

HaierACAdapter::HaierACAdapter(uint8_t irPin) : ac(irPin)
{
}

void HaierACAdapter::begin()
{
    ac.begin();
}

void HaierACAdapter::setPower(bool on)
{
    if (on)
    {
        ac.on();
    }
    else
    {
        ac.off();
    }
}

void HaierACAdapter::setTemp(uint8_t temp)
{
    ac.setTemp(temp);
}

void HaierACAdapter::setFan(FAN::SPEED speed)
{
    uint8_t haierFanSpeed = kHaierAcFanAuto;
    switch (speed)
    {
    case FAN::SLOW:
        haierFanSpeed = kHaierAcFanLow;
        break;
    case FAN::MEDIUM:
        haierFanSpeed = kHaierAcFanMed;
        break;
    case FAN::FAST:
        haierFanSpeed = kHaierAcFanHigh;
        break;
    case FAN::AUTO:
        haierFanSpeed = kHaierAcFanAuto;
        break;
    }
    ac.setFan(haierFanSpeed);
}

void HaierACAdapter::setMode(CLIMATE::MODE mode)
{

    uint8_t haierClimateMode = kHaierAcAuto;
    switch (mode)
    {
    case CLIMATE::COOL:
        haierClimateMode = kHaierAcCool;
        break;
    case CLIMATE::DRY:
        haierClimateMode = kHaierAcDry;
        break;
    case CLIMATE::FAN:
        haierClimateMode = kHaierAcFan;
        break;
    case CLIMATE::HEAT:
        haierClimateMode = kHaierAcHeat;
        break;
    case CLIMATE::AUTO:
        haierClimateMode = kHaierAcAuto;
        break;
    }
    ac.setMode(haierClimateMode);
}

void HaierACAdapter::setSwingV(SWING::MODE_V mode)
{

    uint8_t haierVerticalSwingMode = kHaierAc160SwingVAuto;

    switch (mode)
    {
    case SWING::OFF:
        haierVerticalSwingMode = kHaierAc160SwingVOff;
        break;
    case SWING::TOP:
        haierVerticalSwingMode = kHaierAc160SwingVTop;
        break;
    case SWING::FRONT:
        haierVerticalSwingMode = kHaierAc160SwingVMiddle;
        break;
    case SWING::BOTTOM:
        haierVerticalSwingMode = kHaierAc160SwingVLow;
        break;
    case SWING::DOWN:
        haierVerticalSwingMode = kHaierAc160SwingVLowest;
        break;
    case SWING::AUTO:
        haierVerticalSwingMode = kHaierAc160SwingVAuto;
        break;
    }
    ac.setSwingV(haierVerticalSwingMode);
}

void HaierACAdapter::setHealth(bool on)
{
    ac.setHealth(on);
}

void HaierACAdapter::setTurbo(bool on)
{
    ac.setTurbo(on);
}

void HaierACAdapter::setQuiet(bool on)
{
    ac.setQuiet(on);
}

void HaierACAdapter::setDisplay(bool on)
{
    // Haier AC176 may not have display toggle; implement if available
    (void)on; // Suppress unused parameter warning
}

void HaierACAdapter::send()
{
    ac.send();
}

void HaierACAdapter::printState()
{
    Serial.println("A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
}
