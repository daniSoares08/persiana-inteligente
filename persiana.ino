#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Pinos do motor de passo
const int DIR = 12; // Direção
const int STEP = 14; // Passo
const int steps_per_rev = 200; // Passos por rotação

// Configuração da rede Wi-Fi
const char* ssid = "SSID AQUI"; // Nome da sua rede Wi-Fi
const char* password = "SENHA AQUI"; // Senha da sua rede Wi-Fi

// Instância do servidor web
ESP8266WebServer server(80);

// Variáveis para controle de posição
const int total_steps = 4000; // Total de passos para subir/descer completamente
int current_position = 0; // Posição atual da cortina

// Função para subir a cortina
void subirCortina() {
  Serial.println("Subindo a cortina...");
  digitalWrite(DIR, HIGH); // Define a direção para subir

  for (int i = 0; i < total_steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
    current_position--; // Atualiza a posição
    if (current_position <= 0) break; // Impede ultrapassagem
    yield(); // Evita o reset do watchdog
  }

  Serial.println("Cortina subiu completamente.");
}

// Função para descer a cortina
void descerCortina() {
  Serial.println("Descendo a cortina...");
  digitalWrite(DIR, LOW); // Define a direção para descer

  for (int i = 0; i < total_steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
    current_position++; // Atualiza a posição
    if (current_position >= total_steps) break; // Impede ultrapassagem
    yield(); // Evita o reset do watchdog
  }

  Serial.println("Cortina desceu completamente.");
}

void setup() {
  // Inicializa a Serial
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Configura os pinos do motor
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  // Conecta ao Wi-Fi
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Configura rotas do servidor
  server.on("/", []() {
    server.send(200, "text/plain", "Servidor funcionando!");
    Serial.println("Rota raiz acessada.");
  });

  server.on("/subir", []() {
    Serial.println("Comando recebido: Subir cortina");
    subirCortina();
    server.send(200, "text/plain", "Cortina subindo!");
  });

  server.on("/descer", []() {
    Serial.println("Comando recebido: Descer cortina");
    descerCortina();
    server.send(200, "text/plain", "Cortina descendo!");
  });

  // Inicializa o servidor
  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  // Mantém o servidor ativo
  server.handleClient();
}
