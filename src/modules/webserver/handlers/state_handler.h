#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <ESPAsyncWebServer.h>

void handleStateRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

#endif
