# Projeto IoT - Controle de Luminária com NodeMCU (ESP8266)

## Sumário

- [Descrição](#descrição)
- [Funcionalidades](#funcionalidades)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Instalação](#instalação)
- [Configuração do Ambiente](#configuração-do-ambiente)
- [Como Usar](#como-usar)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Contribuições](#contribuições)
- [Licença](#licença)

## Descrição

Este projeto visa controlar uma luminária RGB utilizando um microcontrolador NodeMCU (ESP8266) através de uma interface web. A interface é embebida diretamente no ESP8266 e pode ser acessada via WebSocket para comunicação em tempo real. O projeto utiliza Vue.js para a interface web, proporcionando uma experiência de usuário moderna e responsiva.

## Funcionalidades

- Controle de intensidade da luz
- Ajuste das cores RGB
- Ligar/Desligar a luminária
- Interface Web responsiva com Vue.js
- Conexão via WebSocket para atualização em tempo real
- Geração de QR Code para fácil acesso à interface

## Tecnologias Utilizadas

- [ESP8266WiFi](https://github.com/esp8266/Arduino)
- [ESP8266mDNS](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS)
- [WebSocketsServer](https://github.com/Links2004/arduinoWebSockets)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [Vue.js](https://vuejs.org/)
- [QRCode](https://github.com/ricmoo/QRCode)

## Instalação

1. Clone o repositório:
   ```sh
   git clone https://github.com/seu-usuario/nodemcu-luminaria.git
