#ifndef IR_MAPPER_H
#define IR_MAPPER_H

#include "../../types/config_types.h"
#include <IRremoteESP8266.h>

// Map config enums to IRremote constants
uint8_t mapClimateMode(CLIMATE::MODE mode);
uint8_t mapFanSpeed(FAN::SPEED mode);
uint8_t mapSwingModeVertical(SWING::MODE_V mode);

#endif