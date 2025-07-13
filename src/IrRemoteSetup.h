#ifndef IR_REMOTE_SETUP_H
#define IR_REMOTE_SETUP_H

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Haier.h>  

extern IRHaierAC176 ac;

void printState();
void setupIR();

#endif