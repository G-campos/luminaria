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
int n = 15;

bool controle ;
bool ctrl = false;
int estado = 0;

void lebotao(){
  ctrl = digitalRead(touch);
  Serial.println(ctrl);
}


void setup() {
  Serial.begin(115200);
  // Inicializa o gerador de números aleatórios com uma semente
  randomSeed(analogRead(A0));

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

  int randomValue1 = random(0, 256);
  int randomValue2 = random(0, 256);
  int randomValue3 = random(0, 256);

  Serial.println(estado);
  switch(estado){
    case 0:
      // clickRele();
      lebotao();
      controle = false;
      if(ctrl == true){
        estado = 1;
      }
    break;

    case 1:
      // clickRele();
      lebotao();
      if(ctrl == false){
        estado = 10;
      }
    break;

    case 10:
      // clickRele();
      webSocket.loop();
      server.handleClient();
      MDNS.update();

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
    // clickRele();
    lebotao();
    if(ctrl == false){
      controle = true;
    }
      if(controle == true){

      digitalWrite(rele, HIGH);
      lebotao();
       if(ctrl == true){
      estado = 21;
        }
      }
    
    break;

    case 21:
      lebotao();
      if(ctrl == false){
        estado = 22;
        digitalWrite(rele, LOW);
      }
    break;

    case 22: //reinicia o ciclo
      controle = false;
      lebotao();
      analogWrite(azul, randomValue1);
      analogWrite(vermelho, randomValue2);
      analogWrite(verde, randomValue3);
      delay(200);
      if(ctrl == true){
        estado = 23;
      }
    break;

    // case 22: //reinicia o ciclo
    //   clickRele();
    //   controle = false;
    //   lebotao();
    //   for(int i = 0; i<255; i = i + n){
    //     lebotao();
    //     analogWrite(azul, i);
    //     delay(100);
    //   }
    //   for(int i = 0; i<255; i = i + n){
    //     lebotao();
    //     analogWrite(vermelho, i);
    //     delay(100);
    //   }
    //   for(int i = 0; i<255; i = i + n){
    //     lebotao();
    //     analogWrite(verde, i);
    //     delay(100);
    //   }
    //   for(int i = 255; i>0; i = i - n){
    //     lebotao();
    //     analogWrite(azul, i);
    //     delay(100);
    //   }
    //   for(int i = 255; i>0; i = i - n){
    //     lebotao();
    //     analogWrite(vermelho, i);
    //     delay(100);
    //   }
    //   for(int i = 255; i>0; i = i - n){
    //     lebotao();
    //     analogWrite(verde, i);
    //     delay(100);
    //   }
    //   if(ctrl == true){
    //     estado = 23;
    //   }
    // break;

    case 23:
    lebotao();
    if(ctrl == false){
      estado = 0;
    }
    break;
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
