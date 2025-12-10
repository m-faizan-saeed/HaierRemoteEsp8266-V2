#ifndef AC_REMOTE_INTERFACE_H
#define AC_REMOTE_INTERFACE_H

#include "../../types/config_types.h"

/**
 * Abstract interface for AC remote control.
 * Allows support for multiple AC brands (Haier, Gree, Daikin, etc.)
 */
class ACRemoteInterface {
public:
    virtual ~ACRemoteInterface() = default;

    // Initialization
    virtual void begin() = 0;

    // Power control
    virtual void setPower(bool on) = 0;

    // Temperature (16-30°C typical)
    virtual void setTemp(uint8_t temp) = 0;

    // Fan speed
    virtual void setFan(FAN::SPEED speed) = 0;

    // Climate mode
    virtual void setMode(CLIMATE::MODE mode) = 0;

    // Swing control (vertical)
    virtual void setSwingV(SWING::MODE_V mode) = 0;

    // Additional features
    virtual void setHealth(bool on) = 0;
    virtual void setTurbo(bool on) = 0;
    virtual void setQuiet(bool on) = 0;
    virtual void setDisplay(bool on) = 0;

    // Send the IR command
    virtual void send() = 0;

    // Debug: print current state
    virtual void printState() = 0;
};

#endif
