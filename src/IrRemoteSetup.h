#ifndef IR_REMOTE_SETUP_H
#define IR_REMOTE_SETUP_H

#include <IRremoteESP8266.h>
#include <IRsend.h>
// #include <ir_Haier.h>
#include <ir_Gree.h>

// extern IRHaierAC176 ac;
extern IRGreeAC ac;

extern bool irRequested;

void setupIR();
void printIrState();
void sendIR();

void handleIR();

#endif