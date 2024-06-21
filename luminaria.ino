#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>
#include <qrcode.h>

#include "network.h"
#include "websocket.h"
#include "httpserver.h"
#include "json.h"

#define azul D1
#define vermelho D7
#define verde D6

#define touch D2
#define rele D5

int red = 0;
int green = 0;
int blue = 0;

bool ctrl = false;
int estado = 0;

void lebotao(){
  ctrl = digitalRead(touch);
  Serial.println(ctrl);
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupMDNS();
  setupWebSocket();
  setupServer();
  String ip = WiFi.localIP().toString();
  String url = "http://" + ip;
  printQRCode(url.c_str());  // Gera e imprime o QR code com o IP
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);

  pinMode(rele, OUTPUT);
  pinMode(touch, INPUT);
}

void loop() {
  // analogWrite(azul, blue);
  // analogWrite(verde, green);
  // analogWrite(vermelho, red);

  webSocket.loop();
  server.handleClient();

  MDNS.update();

  switch(estado){
    case 0:
    digitalWrite(rele, LOW);
    lebotao();
    if(ctrl == true){
      estado = 1;
    }
    break;

    case 1:
    lebotao();
    if(ctrl == false){
      estado = 10;
    }
    break;

    case 10:
    lebotao();
    red = (globalLightIntensity * globalColoRed)/100;
    green = (globalLightIntensity * globalColoGreen)/100;
    blue = (globalLightIntensity * globalColoBlue)/100;
    analogWrite(azul, blue);
    analogWrite(vermelho, red);
    analogWrite(verde, green);
    if(ctrl == true){
      analogWrite(azul, 0);
      analogWrite(vermelho, 0);
      analogWrite(verde, 0);
      estado = 20;
    }
    break;

    case 20:
    lebotao();
    if(ctrl == false){
      digitalWrite(rele, HIGH);
      lebotao();
       if(ctrl == HIGH){
      estado = 21;
      }
    }
    
    break;

    case 21: //reinicia o ciclo
    lebotao();
    digitalWrite(rele, LOW);
    if(ctrl == false){
      for(int i = 0; i<255; i++){
        analogWrite(azul, i);
        delay(10);
      }
      for(int i = 0; i<255; i++){
        analogWrite(vermelho, i);
        delay(10);
      }
      for(int i = 0; i<255; i++){
        analogWrite(verde, i);
        delay(10);
      }
      for(int i = 255; i>0; i--){
        analogWrite(azul, i);
        delay(10);
      }
      for(int i = 255; i>0; i--){
        analogWrite(vermelho, i);
        delay(10);
      }
      for(int i = 255; i>0; i--){
        analogWrite(verde, i);
        delay(10);
      }
    } else {
      estado = 0;
    }
  }
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
