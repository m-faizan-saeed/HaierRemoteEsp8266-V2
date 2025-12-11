#include "ir_remote.h"
#include "haier_ac_adapter.h"
#include "gree_ac_adapter.h"
#include "config/config.h"

// Global AC remote interface pointer
ACRemoteInterface *acRemote = nullptr;

void setupIR()
{
    // Initialize with Haier adapter (D2 = GPIO4)
    // acRemote = new HaierACAdapter(D2);
    acRemote = new GreeACAdapter(D2);
    
    acRemote->begin();
    Serial.println("Default state of the remote.");
    acRemote->printState();
    
    Serial.println("Setting initial state for A/C.");
    acRemote->setPower(false);
    acRemote->setFan(FAN::SLOW);
    acRemote->setMode(CLIMATE::COOL);
    acRemote->setTemp(25);
    acRemote->setSwingV(SWING::AUTO);
    acRemote->printState();
}

void sendIR()
{
    if (acRemote == nullptr) {
        Serial.println("Error: AC remote not initialized!");
        return;
    }

    // Apply current config to remote
    acRemote->setPower(config.power);
    acRemote->setTemp(config.temp);
    acRemote->setMode(config.climateMode);
    acRemote->setFan(config.fan);
    acRemote->setSwingV(config.swingV);
    acRemote->setHealth(config.health);
    acRemote->setTurbo(config.turbo);
    acRemote->setQuiet(config.quiet);
    acRemote->setDisplay(config.disp);

    // Send the IR command
    acRemote->send();
}
