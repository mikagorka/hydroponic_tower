/*
 * Hydroponik Tower Steuerung
 * 
 * Dieses Programm steuert die Pumpe für den Hydroponik-Tower
 * mit einstellbaren Bewässerungsintervallen.
 * 
 * Hardware:
 * - Arduino Uno/Nano oder ESP8266/ESP32
 * - Relais-Modul (5V) zur Pumpensteuerung
 * - VIVOSUN 800GPH Tauchpumpe (3000L/H, 24W)
 * - Optional: Wasserstands-Sensor
 * - Optional: pH/EC Sensoren
 */

// ============ KONFIGURATION ============

// Pin-Definitionen
const int RELAY_PIN = 7;           // Pin für Relais-Steuerung
const int WATER_LEVEL_PIN = A0;    // Analog Pin für Wasserstands-Sensor (optional)
const int LED_PIN = LED_BUILTIN;   // LED zur Status-Anzeige

// Bewässerungs-Zeitsteuerung
const unsigned long PUMP_ON_TIME = 15 * 60 * 1000;  // 15 Minuten Pumpe AN (in Millisekunden)
const unsigned long PUMP_OFF_TIME = 15 * 60 * 1000; // 15 Minuten Pumpe AUS
// Alternative Einstellungen für verschiedene Pflanzen:
// Junge Pflanzen: 10 min AN / 20 min AUS
// Etablierte Pflanzen: 15 min AN / 15 min AUS
// Warmes Wetter: 15 min AN / 10 min AUS

// Wasserstands-Schwellenwerte (optional)
const int WATER_LEVEL_MIN = 200;   // Minimum Wasserpegel

// ============ GLOBALE VARIABLEN ============

unsigned long previousMillis = 0;
bool pumpState = false;
unsigned long pumpRunTime = 0;

void setup() {
  // Serielle Kommunikation für Debugging
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("Hydroponik Tower Steuerung v1.0");
  Serial.println("=================================");
  
  // Pin-Modi setzen
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  
  // Pumpe initial ausschalten
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  pumpState = false;
  
  Serial.println("System initialisiert");
  Serial.print("Pumpe AN Zeit: ");
  Serial.print(PUMP_ON_TIME / 60000);
  Serial.println(" Minuten");
  Serial.print("Pumpe AUS Zeit: ");
  Serial.print(PUMP_OFF_TIME / 60000);
  Serial.println(" Minuten");
  Serial.println();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Prüfe Wasserstand (optional)
  int waterLevel = analogRead(WATER_LEVEL_PIN);
  
  // Zeitbasierte Pumpensteuerung
  if (pumpState) {
    // Pumpe ist AN
    if (currentMillis - previousMillis >= PUMP_ON_TIME) {
      // Pumpe ausschalten
      turnPumpOff();
      previousMillis = currentMillis;
    }
  } else {
    // Pumpe ist AUS
    if (currentMillis - previousMillis >= PUMP_OFF_TIME) {
      // Prüfe Wasserstand bevor Pumpe angeschaltet wird
      if (waterLevel > WATER_LEVEL_MIN || waterLevel == 0) { // waterLevel == 0 wenn kein Sensor
        // Pumpe einschalten
        turnPumpOn();
        previousMillis = currentMillis;
      } else {
        Serial.println("WARNUNG: Wasserstand zu niedrig! Pumpe bleibt AUS.");
        delay(5000); // 5 Sekunden warten vor nächster Prüfung
      }
    }
  }
  
  // Status-Ausgabe alle 30 Sekunden
  static unsigned long lastStatusPrint = 0;
  if (currentMillis - lastStatusPrint >= 30000) {
    printStatus(currentMillis, waterLevel);
    lastStatusPrint = currentMillis;
  }
  
  // LED Blinken wenn Pumpe läuft
  if (pumpState) {
    digitalWrite(LED_PIN, (millis() / 500) % 2); // Blinken alle 500ms
  }
  
  delay(100); // Kurze Pause
}

void turnPumpOn() {
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  pumpState = true;
  pumpRunTime = millis();
  
  Serial.println();
  Serial.println(">>> PUMPE EINGESCHALTET <<<");
  Serial.println();
}

void turnPumpOff() {
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  pumpState = false;
  
  unsigned long runDuration = millis() - pumpRunTime;
  
  Serial.println();
  Serial.println(">>> PUMPE AUSGESCHALTET <<<");
  Serial.print("Laufzeit: ");
  Serial.print(runDuration / 60000);
  Serial.println(" Minuten");
  Serial.println();
}

void printStatus(unsigned long currentMillis, int waterLevel) {
  Serial.println("----- Status -----");
  Serial.print("Zeit seit Start: ");
  Serial.print(currentMillis / 60000);
  Serial.println(" Minuten");
  
  Serial.print("Pumpe: ");
  Serial.println(pumpState ? "AN" : "AUS");
  
  if (pumpState) {
    unsigned long timeRemaining = PUMP_ON_TIME - (currentMillis - previousMillis);
    Serial.print("Noch AN für: ");
    Serial.print(timeRemaining / 60000);
    Serial.println(" Minuten");
  } else {
    unsigned long timeRemaining = PUMP_OFF_TIME - (currentMillis - previousMillis);
    Serial.print("Noch AUS für: ");
    Serial.print(timeRemaining / 60000);
    Serial.println(" Minuten");
  }
  
  if (waterLevel > 0) {
    Serial.print("Wasserstand: ");
    Serial.print(waterLevel);
    Serial.print(" (Min: ");
    Serial.print(WATER_LEVEL_MIN);
    Serial.println(")");
  }
  
  Serial.println("------------------");
  Serial.println();
}
