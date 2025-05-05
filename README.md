# Persiana Automática com ESP8266 e Alexa

Este projeto consiste na automação de uma cortina (persiana) utilizando um microcontrolador ESP8266, um driver de motor A4988 e um motor de passo NEMA 17. A cortina é controlada por comandos de voz via Amazon Alexa, sem necessidade de sensores físicos, utilizando contagem de passos para controle de posição.

---

## 📌 Funcionalidades

- Controle por voz via **Amazon Alexa**
- Integração direta com ESP8266 (NodeMCU) usando a biblioteca `FauxmoESP`
- Motor de passo controlado por driver A4988
- Controle de posição sem sensores físicos, por **contagem de passos**
- Interface web para comandos HTTP (`/subir` e `/descer`)
- Compatível com cortinas leves tipo blackout (até 2m de largura)

---

## 🧰 Materiais Utilizados

| Componente        | Descrição                                       |
|-------------------|-------------------------------------------------|
| ESP8266 (NodeMCU) | Microcontrolador com Wi-Fi                     |
| Motor NEMA 17     | Motor de passo de 200 passos por rotação       |
| Driver A4988      | Driver para controle de motor de passo         |
| Fonte 12V         | Alimentação do motor (mínimo 2A recomendados)  |
| Módulo Relé (opcional) | Para controle de energia ou segurança     |
| Tecido Blackout   | Leve, 2m x 1,5m (ex: poliéster blackout)        |
| Estrutura         | Impressa em 3D ou adaptada para enrolamento    |

---

## 🔌 Esquema de Ligações

- **STEP (GPIO14)** do ESP8266 → **STEP** do A4988  
- **DIR (GPIO12)** do ESP8266 → **DIR** do A4988  
- **VMOT / GND** do A4988 → Fonte 12V  
- **VDD / GND** do A4988 → 3.3V / GND do ESP8266  
- **A+, A- / B+, B-** → Fios do motor de passo  
- **Relé (opcional)** → Controle de alimentação do VMOT

---

## 🚀 Instalação

### 1. Clone este repositório

```bash
git clone https://github.com/seu-usuario/persiana-automatica-esp8266.git
```

### 2. Abra no Arduino IDE

* Instale a placa ESP8266 pela URL de board manager:

  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
* Bibliotecas necessárias:

  * `ESP8266WiFi`
  * `ESP8266WebServer`
  * `fauxmoESP`

### 3. Configure seu Wi-Fi

No arquivo `.ino`, altere as credenciais:

```cpp
const char* ssid = "SEU_WIFI";
const char* password = "SENHA";
```

### 4. Envie para a placa

* Placa: NodeMCU 1.0 (ESP-12E Module)
* Porta correta (COMx)

---

## 🗣️ Comandos com Alexa

Após carregar o código:

1. Abra o app Alexa > Dispositivos > Adicionar dispositivo > **Outro**
2. Aguarde a detecção automática dos dispositivos:

   * `subir cortina`
   * `descer cortina`
3. Comandos disponíveis:

   * "Alexa, **ligar subir cortina**"
   * "Alexa, **ligar descer cortina**"

> Obs: Você pode criar rotinas para comandos como "abrir cortina", "fechar cortina", etc.

---

## 💡 Como funciona sem sensores?

O motor gira um número fixo de passos (ex: 4000) para abrir ou fechar completamente. A posição é mantida em uma variável `current_position`. Com isso, o ESP8266 sabe a posição aproximada da cortina mesmo sem sensores físicos.

---

## 👨‍💻 Autor

**Daniel Soares**
[LinkedIn](https://www.linkedin.com/in/daniel-campos-soares-b47426238/)
