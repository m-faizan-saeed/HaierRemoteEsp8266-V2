#include "ir_mapper.h"
#include <ir_Haier.h>

uint8_t mapClimateMode(CLIMATE::MODE mode)
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

uint8_t mapFanSpeed(FAN::SPEED mode)
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

uint8_t mapSwingModeVertical(SWING::MODE_V mode)
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
