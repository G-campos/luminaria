#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <WebSocketsServer.h>

extern WebSocketsServer webSocket;

// Declaração das variáveis globais
extern bool globalPower;
extern int globalLightIntensity;
extern int globalColoRed;
extern int globalColoGreen;
extern int globalColoBlue;

void setupWebSocket();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

// Declaração das novas funções
void handleWebSocketJson(const char* json);
void sendGlobalData(uint8_t num);

#endif
