#include "httpserver.h"
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);


String ip;

void setupServer() {
  ip = WiFi.localIP().toString();
  server.on("/", handleRoot);
  server.on("/manifest.json", handleManifest);
  server.on("/service-worker.js", handleServiceWorker);
  server.begin();
  Serial.println("HTTP server started");
}

void handleManifest() {
  server.send(200, "application/json", R"({
    "name": "Luminaria",
    "short_name": "Luminaria",
    "start_url": "/",
    "display": "standalone",
    "background_color": "#000000",
    "description": "Controle da luminaria via PWA",
    "icons": [
      {
        "src": "https://cdn.iconscout.com/icon/premium/png-256-thumb/lamp-796-783969.png",
        "sizes": "256x256",
        "type": "image/png"
      }
    ]
  })");
}

void handleServiceWorker() {
  server.send(200, "application/json", R"(
    const CACHE_NAME = 'luminaria-senai-cache-v1';
    const urlsToCache = [
      '/',
      '/index.html',
      '/manifest.json',
      '/favicon.ico',
      // Adicione outros recursos estáticos que você queira que sejam armazenados em cache aqui
    ];
    
    self.addEventListener('install', event => {
      event.waitUntil(
        caches.open(CACHE_NAME)
          .then(cache => {
            console.log('Cache opened');
            return cache.addAll(urlsToCache);
          })
      );
    });
    
    self.addEventListener('fetch', event => {
      event.respondWith(
        caches.match(event.request)
          .then(response => {
            if (response) {
              return response;
            }
            return fetch(event.request);
          })
      );
    });

  )");
}


void handleRoot() {
  server.send(200, "text/html", R"(
<!DOCTYPE html>
    <html lang="pt-BR">
      <head>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <title>Luminaria Senai</title>
        <script src="https://cdn.jsdelivr.net/npm/vue@3.2.47/dist/vue.global.prod.js"></script>
        <!-- Google Icons -->
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@20..48,100..700,0..1,-50..200" />
        <!-- Google Fonts -->
        <link rel="preconnect" href="https://fonts.googleapis.com" />
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
        <link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@600&display=swap" rel="stylesheet" />
        <link rel="manifest" href="/manifest.json" />
        <style>
          .error { color: red; }
          html, body {
            margin: 0;
            padding: 3px;
            font-family: "JetBrains Mono", monospace;
            background-color: black;
            color: lime;
            max-width: 375px;
            max-height: 667px;
          }
          .my-body {
            color: #00ff00;
            font-family: "JetBrains Mono", monospace;
            font-optical-sizing: auto;
            font-weight: 600;
            font-style: normal;
            padding: 2rem;
          }
          .light-power {
            display: flex;
            flex-direction: column;
            align-items: center;
            padding-bottom: 1rem;
          }
          .light-power-span { font-size: 1.2rem; }
          .botao-redondo {
            width: 80px;
            height: 80px;
            border-radius: 50%;
            border-color: #00ff00;
            color: #fff;
            border: none;
            font-size: 30px;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
          }
          .botao-redondo:hover { background-color: #65ff65; }
          .light-intensity, .light-color {
            display: flex;
            flex-direction: column;
            align-items: center;
          }
          .light-intensity-span, .light-color-span { font-size: 1.2rem; }
          .light-intensity-input, .light-color-input {
            width: 200px;
            margin-top: 0.5rem;
          }
          .light-intensity-input::-webkit-slider-thumb {
            background-color: #00ff00;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            cursor: pointer;
            border: none;
          }
          .custom-range {
            -webkit-appearance: none;
            width: 200px;
            height: 8px;
            background: #555;
            border-radius: 5px;
            margin-top: 0.5rem;
            outline: none;
            opacity: 0.8;
            transition: opacity 0.2s;
          }
          .custom-range:hover { opacity: 1; }
          .custom-range::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: lime;
            cursor: pointer;
          }
          .custom-range::-moz-range-thumb {
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: lime;
            cursor: pointer;
          }
          .flex { display: flex; }
          .footer {
            background-color: black; /* Cor de fundo */
            color: lime; /* Cor do texto */
            padding-bottom: 3px; /* Espaçamento interno */
            text-align: center; /* Alinhamento do texto */
            position: fixed; /* Fixa o footer na parte inferior da página */
            left: 0;
            bottom: 0;
            width: 100%; /* Largura total */
          }
        </style>
      </head>
      <body>
        <div id="app">
          <div class="my-body">
            <h3>Conectar ao NodeMCU via WebSocket</h1>
            <div class="light-power">
              <span class="light-power-span">Luz: {{ localLighting.power ? 'Ligada' : 'Desligada'}}</span><br />
              <button class="botao-redondo" @click="togglePower" :style="{ backgroundColor: `rgb(${localLighting.coloRed}, ${localLighting.coloGreen}, ${localLighting.coloBlue})`}">
                <span class="material-symbols-outlined"> power_settings_new </span>
              </button>
            </div>
            <div>
              <div>
                <label class="light-intensity-span">Intensidade:</label>
                <input type="range" min="10" max="100" v-model="localLighting.lightIntensity" class="custom-range" @mousedown.prevent :disabled="!localLighting.power"/>
              </div>
              <div>
                <label>Cor Vermelha: </label>
                <input type="range" min="0" max="255" v-model="localLighting.coloRed" class="custom-range" @mousedown.prevent :disabled="!localLighting.power"/>
              </div>
              <div>
                <label>Cor Verde: </label>
                <input type="range" min="0" max="255" v-model="localLighting.coloGreen" class="custom-range" @mousedown.prevent :disabled="!localLighting.power"/>
              </div>
              <div>
                <label>Cor Azul: </label>
                <input type="range" min="0" max="255" v-model="localLighting.coloBlue" class="custom-range" @mousedown.prevent :disabled="!localLighting.power"/>
              </div>
            </div>
            <footer class="footer"> v {{ version }}</footer>
          </div>
        </div>
        <script>
          const { createApp, ref, onMounted, watch } = Vue;

          createApp({
            setup() {
              const message = ref("");
              const errorMessage = ref("");
              const version = ref("1.0.0")
              const receivingData = ref(false); // Variável de estado para indicar se está recebendo dados
              let localLighting = ref({
                power: false,
                lightIntensity: 0,
                coloRed: 0,
                coloGreen: 0,
                coloBlue: 0,
              });
              let socket;
              const ip = "x.x.x.x"

              const debouncedUpdateLighting = debounce(() => {
                if (!receivingData.value && socket && socket.readyState === WebSocket.OPEN) {
                  socket.send(JSON.stringify(localLighting.value));
                }
              }, 800);
              

              // Função para ativar ou desativar os eventos de mudança nos inputs
              function toggleInputEvents(enable) {
                const inputs = document.querySelectorAll('input[type="range"]');
                inputs.forEach(input => {
                  if (enable) {
                    input.addEventListener('change', debouncedUpdateLighting());
                  } else {
                    input.removeEventListener('change', debouncedUpdateLighting());
                  }
                });
              }

              function debounce(func, delay) {
              let timeoutId;
              
              return function(...args) {
                clearTimeout(timeoutId);
                timeoutId = setTimeout(() => {
                  func.apply(this, args);
                }, delay);
              };
            }

              function calcularAlpha() {
                const alpha = localLighting.lightIntensity / 255;
                return alpha;
              }

              function connect() {
                socket = new WebSocket(`ws://${window.location.hostname}:81`);

                socket.onopen = function () {
                  console.log("Conectado ao WebSocket");
                };

                socket.onmessage = function (event) {
                  const data = JSON.parse(event.data);
                  Object.assign(localLighting.value, data);
                };

                socket.onerror = function (error) {
                  errorMessage.value = "Erro ao conectar: " + error.message;
                };

                socket.onclose = function () {
                  console.log("Desconectado do WebSocket");
                  reconnect();
                };
              }

              function reconnect() {
                setTimeout(() => {
                  console.log("Tentando reconectar...");
                  connect();
                }, 5000); // Tenta reconectar após 5 segundos
              }

              function updateLighting() {
                if (!receivingData.value && socket && socket.readyState === WebSocket.OPEN) {
                  debounce(socket.send(JSON.stringify(localLighting.value)), 200)
                }
              }

              function togglePower() {
                if (localLighting.value.power) {
                  localLighting.value = {
                    power: false,
                    lightIntensity: 0,
                    coloRed: 0,
                    coloGreen: 0,
                    coloBlue: 0,
                  }
                } else {
                  localLighting.value = {
                    power: true,
                    lightIntensity: 10,
                    coloRed: 26,
                    coloGreen: 26,
                    coloBlue: 26,
                  }
                }
              }

              watch(
                () => localLighting.value,
                (newLighting) => {
                  if (newLighting) {
                    debouncedUpdateLighting();
                  }
                },
                { deep: true }
              );

              onMounted(() => {
                connect();
              });

              return {
                message,
                errorMessage,
                localLighting,
                updateLighting,
                togglePower,
                receivingData,
                version,
                debouncedUpdateLighting,
              };
            },
          }).mount("#app");

          if ('serviceWorker' in navigator) {
            // Verifica se já existe um service worker registrado para o escopo da aplicação
            if (navigator.serviceWorker.controller) {
              console.log('Service Worker já registrado.');
            } else {
              // Se não houver um service worker registrado, registra um novo
              navigator.serviceWorker.register('/service-worker.js')
                .then(registration => {
                  console.log('Service Worker registrado com sucesso:', registration);
                }).catch(error => {
                  console.error('Falha ao registrar o Service Worker:', error);
                });
            }
          }
        </script>
      </body>
    </html>
  )");
}
