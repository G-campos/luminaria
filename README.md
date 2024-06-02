# Projeto IoT - Controle de Luminária com NodeMCU (ESP8266)

## Sumário

[Descrição](#descrição)
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
   ```

2. Abra o projeto na IDE Arduino ou PlatformIO.

## Configuração do Ambiente

1. **Instale as bibliotecas necessárias**:
   - ESP8266WiFi
   - ESP8266mDNS
   - WebSocketsServer
   - ArduinoJson
   - QRCode

2. **Configure o WiFi**:
   - No arquivo `network.cpp`, configure as credenciais da sua rede WiFi:
     ```cpp
        const char* ssid = "SEU_SSID";
        const char* password = "SUA_SENHA";
     ```

3. **Compile e envie o código para o NodeMCU**:
   - Conecte o NodeMCU ao computador via USB e selecione a placa e a porta corretas na IDE Arduino ou PlatformIO.
   - Compile e envie o código para o NodeMCU.

## Como Usar

1. **Ligue o NodeMCU**:
   - Após conectar o NodeMCU à rede WiFi, ele exibirá o IP no serial monitor.
   - Escaneie o QR Code exibido no serial monitor ou acesse o IP diretamente no seu navegador.

2. **Acesse a Interface Web**:
   - Utilize o navegador para acessar o IP fornecido.
   - Controle a luminária através da interface web.

## Estrutura do Projeto

```
nodemcu-luminaria/
├── src/
│   ├── main.ino
│   ├── httpserver.cpp
│   ├── httpserver.h
│   ├── json.cpp
│   ├── json.h
│   ├── network.cpp
│   ├── network.h
│   ├── websocket.cpp
│   ├── websocket.h
├── data/
│   ├── index.html
├── README.md
```

### Arquivos principais:

- `main.ino`: Arquivo principal que configura e gerencia a execução do programa.
- `httpserver.cpp/h`: Configuração e manipulação do servidor HTTP.
- `json.cpp/h`: Tratamento de dados JSON.
- `network.cpp/h`: Configuração da rede WiFi e mDNS.
- `websocket.cpp/h`: Configuração e manipulação do WebSocket.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.

1. Fork o projeto
2. Crie uma nova branch (`git checkout -b feature/nova-funcionalidade`)
3. Commit suas mudanças (`git commit -am 'Adicionei nova funcionalidade'`)
4. Push para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um Pull Request

## Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
```

Este arquivo `README.md` fornece uma visão geral completa do seu projeto, incluindo uma descrição, funcionalidades, tecnologias utilizadas, instruções de instalação e configuração, como usar, a estrutura do projeto, como contribuir e informações de licença. Ajuste conforme necessário para refletir detalhes específicos do seu projeto.
