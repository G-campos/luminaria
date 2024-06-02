#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <qrcode.h>  // Inclua a biblioteca QRCode

#include "network.h"
#include "websocket.h"
#include "httpserver.h"
#include "json.h"

void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupMDNS();
  setupWebSocket();
  setupServer();
  String ip = WiFi.localIP().toString();
  String url = "http://" + ip;
  printQRCode(url.c_str());  // Gera e imprime o QR code com o IP
}

void loop() {
  webSocket.loop();
  server.handleClient();
  MDNS.update();
}

void printQRCode(const char* url) {
  const int qrCodeVersion = 3;
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(qrCodeVersion)];

  qrcode_initText(&qrcode, qrcodeData, qrCodeVersion, ECC_MEDIUM, url);

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        Serial.print("█");  // Para um pixel preto
      } else {
        Serial.print(" ");  // Para um pixel branco
      }
    }
    Serial.println();
  }
}
