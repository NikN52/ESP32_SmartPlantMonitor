#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <BH1750.h>

// Настройки Wi-Fi
const char* ssid = "your_ssid";
const char* password = "your_password";

// Настройка DHT22
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dhtSensor(DHTPIN, DHTTYPE);

// Настройка BH1750
BH1750 lightSensor;

// Настройка влажности почвы
#define SOIL_MOISTURE_PIN 34

// Настройка насоса и подсветки
#define PUMP_PIN 25
#define LIGHT_PIN 26

// Веб-сервер
WebServer server(80);

// Функции для работы с датчиками и компонентами системы
int readSoilMoisture(int soilMoisturePin);
void readDHTData(DHT &dhtSensor, float &temperature, float &humidity);
uint16_t readLightIntensity(BH1750 &lightSensor);
void autoWatering(int soilMoisture, int threshold, int pumpPin);
void autoLighting(uint16_t lightIntensity, uint16_t threshold, int lightPin);
void connectToWiFi(const char *ssid, const char *password);

// Функции для работы с веб-сервером
void handleRoot();
void handlePump();
void handleLight();
void handleGraphs();
String generateGraphs();

unsigned long lastUpdateTime = 0;
const int updateInterval = 5000; // обновление графиков каждые 5 секунд

void setup() {
  Serial.begin(115200);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  
  dhtSensor.begin();
  lightSensor.begin();
  
  connectToWiFi(ssid, password);
  
  server.on("/", handleRoot);
  server.on("/pump", handlePump);
  server.on("/light", handleLight);
  server.on("/graphs", handleGraphs);

  server.begin();
}

void loop() {
  if (millis() - lastUpdateTime > updateInterval) {
    lastUpdateTime = millis();
	float temperature, humidity;
	readDHTData(dhtSensor, temperature, humidity);
	int soilMoisture = readSoilMoisture(SOIL_MOISTURE_PIN);
	uint16_t lightIntensity = readLightIntensity(lightSensor);

	autoWatering(soilMoisture, 700, PUMP_PIN);
	autoLighting(lightIntensity, 200, LIGHT_PIN);
  }
  
  server.handleClient();
}

int readSoilMoisture(int soilMoisturePin) {
  int soilMoisture = analogRead(soilMoisturePin);
  return soilMoisture;
}

void readDHTData(DHT &dhtSensor, float &temperature, float &humidity) {
  temperature = dhtSensor.readTemperature();
  humidity = dhtSensor.readHumidity();
}

uint16_t readLightIntensity(BH1750 &lightSensor) {
  uint16_t lightIntensity = lightSensor.readLightLevel();
  return lightIntensity;
}

void autoWatering(int soilMoisture, int threshold, int pumpPin) {
  if (soilMoisture < threshold) {
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpPin, LOW);
  }
}

void autoLighting(uint16_t lightIntensity, uint16_t threshold, int lightPin) {
  if (lightIntensity < threshold) {
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }
}

void connectToWiFi(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void handleRoot() {
  String html = "<html><head><title>SmartPlantMonitor</title></head><body>";
  html += "<h1>SmartPlantMonitor</h1>";
  html += "<p><a href=\"/pump\">Включить/выключить полив</a></p>";
  html += "<p><a href=\"/light\">Включить/выключить подсветку</a></p>";
  html += "<p><a href=\"/graphs\">Показать графики</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handlePump() {
  int pumpState = digitalRead(PUMP_PIN);
  digitalWrite(PUMP_PIN, !pumpState);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLight() {
  int lightState = digitalRead(LIGHT_PIN);
  digitalWrite(LIGHT_PIN, !lightState);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleGraphs() {
  server.send(200, "text/html", generateGraphs());
}

String generateGraphs() {
  String html = "<html><head><title>SmartPlantMonitor - Графики</title>";
  html += "<meta http-equiv=\"refresh\" content=\"5\"/>"; // автоматическое обновление страницы каждые 5 секунд
  html += "</head><body>";
  html += "<h1>SmartPlantMonitor - Графики</h1>";
  html += "<h2>Температура: " + String(temperature) + " °C</h2>";
  html += "<h2>Влажность воздуха: " + String(humidity) + " %</h2>";
  html += "<h2>Влажность почвы: " + String(soilMoisture) + "</h2>";
  html += "<h2>Освещенность: " + String(lightIntensity) + " lux</h2>";

  html += "<h3>Температура</h3>";
  html += "<svg width=\"100%\" height=\"100\" viewBox=\"0 0 1024 100\" preserveAspectRatio=\"none\">";
  html += "<polyline points=\"0," + String(100 - temperature) + " 1024," + String(100 - temperature) + "\" stroke=\"red\" stroke-width=\"2\"/>";
  html += "</svg>";

  html += "<h3>Влажность воздуха</h3>";
  html += "<svg width=\"100%\" height=\"100\" viewBox=\"0 0 1024 100\" preserveAspectRatio=\"none\">";
  html += "<polyline points=\"0," + String(100 - humidity) + " 1024," + String(100 - humidity) + "\" stroke=\"blue\" stroke-width=\"2\"/>";
  html += "</svg>";

  html += "<h3>Влажность почвы</h3>";
  html += "<svg width=\"100%\" height=\"100\" viewBox=\"0 0 1024 100\" preserveAspectRatio=\"none\">";
  html += "<polyline points=\"0," + String(100 - (soilMoisture / 10)) + " 1024," + String(100 - (soilMoisture / 10)) + "\" stroke=\"green\" stroke-width=\"2\"/>";
  html += "</svg>";

  html += "<h3>Освещенность</h3>";
  html += "<svg width=\"100%\" height=\"100\" viewBox=\"0 0 1024 100\" preserveAspectRatio=\"none\">";
  html += "<polyline points=\"0," + String(100 - (lightIntensity / 655)) + " 1024," + String(100 - (lightIntensity / 655)) + "\" stroke=\"yellow\" stroke-width=\"2\"/>";
  html += "</svg>";

  html += "</body></html>";

  return html;
}
