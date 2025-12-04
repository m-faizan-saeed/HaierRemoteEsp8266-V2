#ifndef IR_REMOTE_H
#define IR_REMOTE_H

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Haier.h>  

extern IRHaierAC176 ac;

void printState();

void setupIR();

void sendIR();

#endif