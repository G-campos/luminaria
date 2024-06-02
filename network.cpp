#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
#else
  #error "Plataforma não suportada"
#endif


#include "network.h"

const char* ssid = "GABRILMHNET";
const char* password = "76393822";
const char* hostName = "luminaria";

void setupWiFi() {
  WiFi.begin(ssid, password);
  pinMode(LED_BUILTIN, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setupMDNS() {
  if (MDNS.begin(hostName)) {
    Serial.println("MDNS responder started");
    MDNS.addService("http", "tcp", 80);
    Serial.print("You can now connect to http://");
    Serial.print(hostName);
    Serial.println(".local");
  } else {
    Serial.println("Error setting up MDNS responder");
  }
}
