#ifndef IR_REMOTE_H
#define IR_REMOTE_H

#include "ac_remote_interface.h"

// Global AC remote instance (can be Haier, Gree, or other brand)
extern ACRemoteInterface *acRemote;

void setupIR();
void sendIR();

#endif#endif