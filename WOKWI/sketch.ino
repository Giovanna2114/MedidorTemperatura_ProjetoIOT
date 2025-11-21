/******************************************************
 * PROJETO IoT Mackenzie – Monitoramento de Temperatura
 * ESP32 + DHT22 + LCD I2C + RELÉ + MQTT + Controle Automático
 ******************************************************/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// ============ CONFIGURAÇÃO DO DHT22 ============
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ============ LCD 16x2 I2C ============
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ============ RELÉ ============
#define RELE_PIN 5   // GPIO5
bool ventiladorLigado = false;

// ============ WIFI ============
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ============ MQTT ============
const char* mqtt_server = "test.mosquitto.org";

const char* topic_temp = "giovanna/leito1/temperatura";
const char* topic_umid = "giovanna/leito1/umidade";
const char* topic_cmd  = "giovanna/leito1/ventilador";

WiFiClient espClient;
PubSubClient client(espClient);

// ===== VARIÁVEIS DE SIMULAÇÃO =====
float tempSimulada = 27.0;   
float umidadeSimulada = 60.0;

void reconnectMQTT() {
  while (!client.connected()) {
    if (client.connect("ESP32-Giovanna-Leito")) {
      client.subscribe(topic_cmd);
    } else {
      delay(1500);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String comando = "";

  for (int i = 0; i < length; i++) {
    comando += (char)message[i];
  }

  if (comando == "ON") {
    ventiladorLigado = true;
    digitalWrite(RELE_PIN, LOW);
  }
  else if (comando == "OFF") {
    ventiladorLigado = false;
    digitalWrite(RELE_PIN, HIGH);
  }
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);

  lcd.init();
  lcd.backlight();

  dht.begin();
  setupWiFi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // ============================================
  // SIMULAÇÃO DA TEMPERATURA DO QUARTO
  // ============================================

  tempSimulada += (random(-3, 4) * 0.1);

  // Se o ventilador está ligado → resfriar
  if (ventiladorLigado) {
    tempSimulada -= 0.25;   // taxa de resfriamento
  }

  // Mantém dentro de limites realistas
  if (tempSimulada < 18) tempSimulada = 18;
  if (tempSimulada > 35) tempSimulada = 35;

  // ============================================
  // CONTROLE AUTOMÁTICO DO VENTILADOR
  // ============================================
  if (tempSimulada > 25.0) {
    ventiladorLigado = true;
    digitalWrite(RELE_PIN, LOW);
  }
  if (tempSimulada <= 24.0) {
    ventiladorLigado = false;
    digitalWrite(RELE_PIN, HIGH);
  }

  // ============================================
  // LCD
  // ============================================
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempSimulada, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Vent: ");
  lcd.print(ventiladorLigado ? "ON " : "OFF");

  // ============================================
  // PUBLICAÇÃO MQTT
  // ============================================
  client.publish(topic_temp, String(tempSimulada).c_str());
  client.publish(topic_umid, String(umidadeSimulada).c_str());

  Serial.print("Temp: ");
  Serial.print(tempSimulada);
  Serial.print(" | Vent: ");
  Serial.println(ventiladorLigado ? "ON" : "OFF");

  delay(2000);
}
