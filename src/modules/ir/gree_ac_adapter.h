#ifndef GREE_AC_ADAPTER_H
#define GREE_AC_ADAPTER_H

#include "ac_remote_interface.h"
#include <ir_Gree.h>

/**
 * Adapter for Gree AC remote control.
 * Wraps IRremoteESP8266's Gree implementation.
 */
class GreeACAdapter : public ACRemoteInterface {
private:
    IRGreeAC ac;

public:
    GreeACAdapter(uint8_t irPin);
    virtual ~GreeACAdapter() = default;

    void begin() override;
    void setPower(bool on) override;
    void setTemp(uint8_t temp) override;
    void setFan(FAN::SPEED speed) override;
    void setMode(CLIMATE::MODE mode) override;
    void setSwingV(SWING::MODE_V mode) override;
    void setHealth(bool on) override;
    void setTurbo(bool on) override;
    void setQuiet(bool on) override;
    void setDisplay(bool on) override;
    void send() override;
    void printState() override;
};

#endif
