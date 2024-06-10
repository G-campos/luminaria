#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void setupServer();
void handleRoot();
void handleManifest();
void handleServiceWorker();

#endif
