#ifndef HAIER_AC_ADAPTER_H
#define HAIER_AC_ADAPTER_H

#include "ac_remote_interface.h"
#include <ir_Haier.h>

/**
 * Adapter for Haier AC remote control.
 * Wraps IRremoteESP8266's Haier implementation.
 */
class HaierACAdapter : public ACRemoteInterface {
private:
    IRHaierAC176 ac;

public:
    HaierACAdapter(uint8_t irPin);
    virtual ~HaierACAdapter() = default;

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
