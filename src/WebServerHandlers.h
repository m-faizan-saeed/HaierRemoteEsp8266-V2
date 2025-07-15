#ifndef WEB_SERVER_HANDLERS_H
#define WEB_SERVER_HANDLERS_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void setupWebServer();

void handleServer();

#endif