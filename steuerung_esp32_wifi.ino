/*
 * Hydroponik Tower Steuerung - ESP32 Version mit WiFi
 * 
 * Erweiterte Steuerung mit:
 * - WiFi-Verbindung
 * - Web-Interface zur Überwachung
 * - MQTT Support (optional)
 * - Erweiterte Sensor-Unterstützung
 * 
 * Hardware:
 * - ESP32 Development Board
 * - Relais-Modul (3.3V oder 5V)
 * - VIVOSUN 800GPH Tauchpumpe
 * - Optional: DHT22 (Temperatur/Luftfeuchtigkeit)
 * - Optional: Wasserstands-Sensor
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ============ KONFIGURATION ============

// WiFi Einstellungen
const char* ssid = "DEIN_WIFI_NAME";          // WiFi Name hier eintragen
const char* password = "DEIN_WIFI_PASSWORT";  // WiFi Passwort hier eintragen

// Pin-Definitionen
const int RELAY_PIN = 26;          // GPIO26 für Relais
const int DHT_PIN = 4;             // GPIO4 für DHT22 Sensor
const int WATER_LEVEL_PIN = 34;    // GPIO34 (ADC) für Wasserstand
const int LED_PIN = 2;             // Eingebaute LED

// DHT Sensor Typ
#define DHTTYPE DHT22

// Bewässerungs-Zeitsteuerung (in Millisekunden)
unsigned long pumpOnTime = 15 * 60 * 1000;   // 15 Minuten
unsigned long pumpOffTime = 15 * 60 * 1000;  // 15 Minuten

// Wasserstands-Schwellenwerte
const int WATER_LEVEL_MIN = 500;

// ============ OBJEKTE ============

WebServer server(80);
DHT dht(DHT_PIN, DHTTYPE);

// ============ GLOBALE VARIABLEN ============

unsigned long previousMillis = 0;
bool pumpState = false;
unsigned long pumpRunTime = 0;
unsigned long totalPumpRuntime = 0;
int pumpCycles = 0;

// Sensor-Werte
float temperature = 0;
float humidity = 0;
int waterLevel = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=================================");
  Serial.println("Hydroponik Tower Steuerung v2.0");
  Serial.println("ESP32 WiFi Edition");
  Serial.println("=================================\n");
  
  // Pin-Modi setzen
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  
  // Pumpe initial ausschalten
  digitalWrite(RELAY_PIN, LOW);
  pumpState = false;
  
  // DHT Sensor initialisieren
  dht.begin();
  
  // WiFi verbinden
  connectToWiFi();
  
  // Webserver Routen
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/control", handleControl);
  server.on("/settings", handleSettings);
  
  server.begin();
  Serial.println("Webserver gestartet");
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  server.handleClient();
  
  unsigned long currentMillis = millis();
  
  // Sensoren alle 5 Sekunden lesen
  static unsigned long lastSensorRead = 0;
  if (currentMillis - lastSensorRead >= 5000) {
    readSensors();
    lastSensorRead = currentMillis;
  }
  
  // Zeitbasierte Pumpensteuerung
  if (pumpState) {
    if (currentMillis - previousMillis >= pumpOnTime) {
      turnPumpOff();
      previousMillis = currentMillis;
    }
  } else {
    if (currentMillis - previousMillis >= pumpOffTime) {
      if (waterLevel > WATER_LEVEL_MIN || waterLevel == 0) {
        turnPumpOn();
        previousMillis = currentMillis;
      } else {
        Serial.println("WARNUNG: Wasserstand zu niedrig!");
      }
    }
  }
  
  // LED Blinken wenn Pumpe läuft
  if (pumpState) {
    digitalWrite(LED_PIN, (millis() / 500) % 2);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(10);
}

void connectToWiFi() {
  Serial.print("Verbinde mit WiFi");
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Verbunden!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(" Fehler!");
    Serial.println("Fahre ohne WiFi fort...");
  }
}

void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  waterLevel = analogRead(WATER_LEVEL_PIN);
  
  if (isnan(temperature) || isnan(humidity)) {
    temperature = 0;
    humidity = 0;
  }
}

void turnPumpOn() {
  digitalWrite(RELAY_PIN, HIGH);
  pumpState = true;
  pumpRunTime = millis();
  pumpCycles++;
  
  Serial.println("\n>>> PUMPE EINGESCHALTET <<<");
  Serial.print("Zyklus #");
  Serial.println(pumpCycles);
}

void turnPumpOff() {
  digitalWrite(RELAY_PIN, LOW);
  pumpState = false;
  
  unsigned long runDuration = millis() - pumpRunTime;
  totalPumpRuntime += runDuration;
  
  Serial.println("\n>>> PUMPE AUSGESCHALTET <<<");
  Serial.print("Laufzeit: ");
  Serial.print(runDuration / 60000);
  Serial.println(" Minuten\n");
}

// ============ WEBSERVER HANDLER ============

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Hydroponik Tower Steuerung</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; max-width: 800px; margin: 50px auto; padding: 20px; background: #f0f0f0; }";
  html += ".container { background: white; padding: 30px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }";
  html += "h1 { color: #2ecc71; text-align: center; }";
  html += ".status-box { background: #ecf0f1; padding: 20px; margin: 20px 0; border-radius: 5px; }";
  html += ".status-item { margin: 10px 0; font-size: 18px; }";
  html += ".pump-on { color: #27ae60; font-weight: bold; }";
  html += ".pump-off { color: #e74c3c; font-weight: bold; }";
  html += "button { background: #3498db; color: white; border: none; padding: 15px 30px; font-size: 16px; border-radius: 5px; cursor: pointer; margin: 5px; }";
  html += "button:hover { background: #2980b9; }";
  html += ".controls { text-align: center; margin: 20px 0; }";
  html += ".sensor { display: inline-block; background: #3498db; color: white; padding: 15px; margin: 10px; border-radius: 5px; min-width: 150px; }";
  html += ".sensor-value { font-size: 24px; font-weight: bold; }";
  html += "</style>";
  html += "<script>";
  html += "function updateStatus() {";
  html += "  fetch('/status').then(r => r.json()).then(data => {";
  html += "    document.getElementById('pump-status').innerHTML = data.pumpOn ? '<span class=\"pump-on\">AN</span>' : '<span class=\"pump-off\">AUS</span>';";
  html += "    document.getElementById('temp').innerText = data.temperature.toFixed(1);";
  html += "    document.getElementById('humidity').innerText = data.humidity.toFixed(1);";
  html += "    document.getElementById('water').innerText = data.waterLevel;";
  html += "    document.getElementById('cycles').innerText = data.cycles;";
  html += "    document.getElementById('runtime').innerText = Math.floor(data.totalRuntime / 60);";
  html += "  });";
  html += "}";
  html += "setInterval(updateStatus, 2000);";
  html += "window.onload = updateStatus;";
  html += "</script>";
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>🌱 Hydroponik Tower Steuerung</h1>";
  
  html += "<div class='status-box'>";
  html += "<div class='status-item'>Pumpe: <span id='pump-status'>" + String(pumpState ? "<span class='pump-on'>AN</span>" : "<span class='pump-off'>AUS</span>") + "</span></div>";
  html += "<div class='status-item'>Zyklen: <span id='cycles'>" + String(pumpCycles) + "</span></div>";
  html += "<div class='status-item'>Gesamtlaufzeit: <span id='runtime'>" + String(totalPumpRuntime / 60000) + "</span> Minuten</div>";
  html += "</div>";
  
  html += "<div style='text-align: center;'>";
  html += "<div class='sensor'>";
  html += "<div>Temperatur</div>";
  html += "<div class='sensor-value'><span id='temp'>" + String(temperature, 1) + "</span>°C</div>";
  html += "</div>";
  html += "<div class='sensor'>";
  html += "<div>Luftfeuchtigkeit</div>";
  html += "<div class='sensor-value'><span id='humidity'>" + String(humidity, 1) + "</span>%</div>";
  html += "</div>";
  html += "<div class='sensor'>";
  html += "<div>Wasserstand</div>";
  html += "<div class='sensor-value'><span id='water'>" + String(waterLevel) + "</span></div>";
  html += "</div>";
  html += "</div>";
  
  html += "<div class='controls'>";
  html += "<button onclick=\"fetch('/control?action=on')\">Pumpe AN</button>";
  html += "<button onclick=\"fetch('/control?action=off')\">Pumpe AUS</button>";
  html += "</div>";
  
  html += "<div style='text-align: center; margin-top: 30px; color: #7f8c8d;'>";
  html += "<small>IP: " + WiFi.localIP().toString() + " | Uptime: " + String(millis() / 60000) + " min</small>";
  html += "</div>";
  
  html += "</div></body></html>";
  
  server.send(200, "text/html", html);
}

void handleStatus() {
  String json = "{";
  json += "\"pumpOn\":" + String(pumpState ? "true" : "false") + ",";
  json += "\"temperature\":" + String(temperature) + ",";
  json += "\"humidity\":" + String(humidity) + ",";
  json += "\"waterLevel\":" + String(waterLevel) + ",";
  json += "\"cycles\":" + String(pumpCycles) + ",";
  json += "\"totalRuntime\":" + String(totalPumpRuntime) + "";
  json += "}";
  
  server.send(200, "application/json", json);
}

void handleControl() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    if (action == "on" && !pumpState) {
      turnPumpOn();
      previousMillis = millis();
    } else if (action == "off" && pumpState) {
      turnPumpOff();
      previousMillis = millis();
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleSettings() {
  if (server.hasArg("onTime")) {
    pumpOnTime = server.arg("onTime").toInt() * 60000;
  }
  if (server.hasArg("offTime")) {
    pumpOffTime = server.arg("offTime").toInt() * 60000;
  }
  
  String json = "{";
  json += "\"onTime\":" + String(pumpOnTime / 60000) + ",";
  json += "\"offTime\":" + String(pumpOffTime / 60000);
  json += "}";
  
  server.send(200, "application/json", json);
}
