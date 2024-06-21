#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
extern ESP8266WebServer server;


void setupServer();
void handleRoot();
void handleManifest();
void handleServiceWorker();

#endif
