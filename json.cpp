#include <ArduinoJson.h>
#include "httpserver.h" // Inclua o arquivo de cabeçalho onde o servidor é declarado externamente
#include "json.h"

void sendJson() {
  StaticJsonDocument<200> doc;
  doc["led1"] = 1;
  doc["led2"] = 0;

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}
