#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "json.h"

extern ESP8266WebServer server;

void sendJson() {
  StaticJsonDocument<200> doc;
  doc["led1"] = 1;
  doc["led2"] = 0;

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}
