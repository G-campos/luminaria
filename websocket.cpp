#include "websocket.h"

// Variáveis globais para armazenar o estado da iluminação
bool globalPower = false;
int globalLightIntensity = 0;
int globalColoRed = 0;
int globalColoGreen = 0;
int globalColoBlue = 0;

WebSocketsServer webSocket(81);

void setupWebSocket() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

// Função para tratar o JSON recebido via WebSocket
void handleWebSocketJson(const char* json) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, json);

  // Verifica se houve erro na desserialização
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Obtém os valores do JSON e atualiza as variáveis globais correspondentes
  if (doc.containsKey("power")) {
    globalPower = doc["power"];
  }

  if (doc.containsKey("lightIntensity")) {
    globalLightIntensity = doc["lightIntensity"];
  }

  if (doc.containsKey("coloRed")) {
    globalColoRed = doc["coloRed"];
  }

  if (doc.containsKey("coloGreen")) {
    globalColoGreen = doc["coloGreen"];
  }

  if (doc.containsKey("coloBlue")) {
    globalColoBlue = doc["coloBlue"];
  }
}

// Função para enviar os dados globais para uma nova sessão
void sendGlobalData(uint8_t num) {
  StaticJsonDocument<200> doc;
  // Preencha o JSON com os dados globais
  doc["power"] = globalPower;
  doc["lightIntensity"] = globalLightIntensity;
  doc["coloRed"] = globalColoRed;
  doc["coloGreen"] = globalColoGreen;
  doc["coloBlue"] = globalColoBlue;

  String json;
  serializeJson(doc, json);

  webSocket.sendTXT(num, json);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      webSocket.sendTXT(num, "Connected");
      
      // Envie os dados globais ao conectar uma nova sessão
      sendGlobalData(num);
      break;
    }
    case WStype_TEXT:
      Serial.printf("[%u] Received Text: %s\n", num, payload);
      handleWebSocketJson((const char*)payload);
      
      // Reenvia os dados atualizados para todas as sessões conectadas
      webSocket.broadcastTXT((const char*)payload);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      break;
  }
}
