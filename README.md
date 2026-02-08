# 🌱 DIY Hydroponic Tower Projekt – Zusammenfassung aller wichtigen Infos

Dies ist eine vollständige Zusammenfassung aller Erkenntnisse, Tipps und Abläufe, die wir rund um deinen Hydroponik-Tower zusammengestellt haben.

## 🚀 Automatisierung & Steuerung - Quick Links

**Neu: Automatische Pumpensteuerung verfügbar!**

- 📘 **[QUICK START - In 30 Minuten zur Automatisierung](QUICK_START.md)**
- 🔧 **[Verkabelungs-Anleitung mit Schaltplänen](VERKABELUNG.md)**
- 🛒 **[Einkaufsliste - Alle benötigten Komponenten](EINKAUFSLISTE.md)**
- ❓ **[FAQ - Häufig gestellte Fragen & Problemlösung](FAQ.md)**
- 💻 **Arduino Code:** `steuerung_arduino.ino`
- 📡 **ESP32 WiFi Code:** `steuerung_esp32_wifi.ino`

**Vorteile der Automatisierung:**
- ✅ Pumpe läuft automatisch in einstellbaren Intervallen
- ✅ Keine manuelle Steuerung nötig
- ✅ Optional: WiFi-Steuerung & Web-Interface
- ✅ Sensoren für Wasserstand, Temperatur, Luftfeuchtigkeit
- ✅ Kosten: Ab ~30€ für komplette Automatisierung

---
![Hydro Tower indoor](images/IMG_7189.jpeg)
![Hydro Tower outdoor](images/IMG_8450.jpeg)

## 📦 Produkte & Komponenten

### 🧪 Dünger & Nährstoffe
- **Terra Aquatica TriPart** - Professionelles 3-Komponenten-Düngesystem für Hydroponik
  - [Terra Aquatica TriPart](https://www.terraaquatica.com/mineral-fertiliser-solutions/tripart/)

### 💧 Pumpe & Bewässerung
- **VIVOSUN 800GPH Tauchpumpe** (3000L/H, 24W) oder vergleichbare Pumpe mit ähnlicher Leistung
- **PVC-Schlauch** für die Wasserverteilung

### 🌱 Keimmedium
- **Steinwolle** als Keimmedium

### 🌡️ Zusätzliche Ausstattung
- **Keimstation** mit transparentem oder abgedunkeltem Deckel (je nach Samen)
- **Heizmatte** zur Keimunterstützung (v. a. für Paprika & Gurken)
- **Lichtpanel mit 3 Modi**: Weiß, Rot+Blau, Rot+Blau+Weiß
- **Hydroponik-Tower** mit Wasserbehälter & Pumpe

### 🤖 Automatisierung & Steuerung
- **Arduino Uno/Nano** oder **ESP8266/ESP32** für automatische Pumpensteuerung
- **Relais-Modul (5V)** zur Ansteuerung der Pumpe
- **Optional: DHT22 Sensor** für Temperatur & Luftfeuchtigkeit
- **Optional: Wasserstands-Sensor** zur Überwachung des Füllstands
- **Optional: pH/EC Sensoren** für präzise Nährstoffkontrolle
- Siehe [Steuerungscode](#-steuerung--automatisierung) für fertige Lösungen

---

## 🌡️ Temperatur- & Lichtanforderungen pro Pflanze

| Pflanze        | Keimtyp       | Temp. optimal | Lichtbedarf nach Keimung |
|----------------|---------------|---------------|----------------------------|
| Paprika        | Dunkelkeimer  | 25–28 °C      | Hoch (Rot+Blau empfohlen)  |
| Gurke          | Dunkelkeimer  | 22–28 °C      | Hoch (Vollspektrum ideal) |
| Basilikum      | Lichtkeimer   | 20–25 °C      | Hoch                       |
| Petersilie     | Dunkelkeimer  | 18–22 °C      | Mittel                     |
| Romana-Salat   | Lichtkeimer   | 15–20 °C      | Mittel                     |
| Rucola         | Lichtkeimer   | 15–22 °C      | Mittel                     |

---

## 🌱 Keimung: Samenmenge & Handhabung

- **Paprika, Gurke**: 1–2 Samen pro Würfel, schwächeren Keimling später abschneiden
- **Romana, Rucola**: 2 Samen pro Würfel, auf besten Keimling selektieren
- **Basilikum, Petersilie**: 1–2 Samen; bei Basilikum auch Mehrfachaussaat möglich

**Dunkelkeimer**: leicht mit Steinwollfussel abdecken oder vollständig abdunkeln  
**Lichtkeimer**: nicht abdecken, direktes Licht nach Keimung

---

## 💡 Lichtphasen & Spektren

| Phase        | Spektrum            | Dauer/Tag     |
|--------------|---------------------|---------------|
| Keimphase    | Weiß (leicht) oder Dunkel | 0–16 h     |
| Nach Keimung | Weiß oder R+B+W     | 14–16 h       |
| Fruchtbildung| Rot+Blau bevorzugt  | 12–14 h       |

---

## 💧 pH-Wert & Bewässerung

- **Steinwolle wässern mit pH 5,5–6,0**
- **Wasser im Tray**: nur Boden der Steinwolle berühren lassen
- **Kein stehendes Wasser** im oberen Bereich
- Nach dem Einsetzen in den Tower: pH regelmäßig messen & Nährlösung anpassen

---

## 🧪 Nährstoffversorgung

- **Keimphase:** nur pH-angepasstes Wasser
- **Nach Keimung (ab 2–3 echte Blätter):** schwache Nährlösung (EC 0.6–0.8)
- **Im Tower:** reguläre Hydro-Nährlösung (je nach Pflanzenart anpassen)

---

## 🌿 Umpflanz-Checkliste

- 2–3 Blattpaare sichtbar
- Starke, kompakte Pflanze
- Wurzeln kommen aus Steinwolle raus
- Steinwollwürfel kann in größeren Würfel oder direkt in Netztopf gesteckt werden

---

## 🌡️ Outdoor-Betrieb

| Pflanze      | Mindest-Tagestemp. | Außeneinsatz geeignet? |
|--------------|--------------------|--------------------------|
| Paprika      | >20 °C             | ❌ Zu empfindlich bei <15 °C |
| Gurke        | >18 °C             | ❌ Zu empfindlich          |
| Romana       | >10 °C             | ✅ Ja, robust              |

Empfehlung: Bei Outdoor-Einsatz → Mini-Gewächshaus, Windschutz, ggf. Isolierung

---

## ⚠️ Schimmel / Rückstände in Steinwolle

- Leichte weiße Punkte = meist **Salzrückstände**, nicht gefährlich
- Flauschig/weiß → **leichter Oberflächenschimmel**
- Maßnahmen:
  - Oberfläche abtrocknen lassen
  - Luftzirkulation verbessern
  - ggf. leicht mit verd. Wasserstoffperoxid abwischen

---

## ✅ Sonstige Tipps

- Samen nicht zu tief setzen (0.5–1 cm)
- Nicht mehrmals täglich sprühen, lieber passiv bewässern von unten
- Dunkelkeimer ohne Abdeckung möglich, wenn Umgebung komplett dunkel

### 📺 Hilfreiche Video-Ressourcen

- **Hydroponic Tower Setup & Tipps**: [YouTube Video](https://www.youtube.com/watch?v=HjOwOpKufG0&t=198s)

---

## 🤖 Steuerung & Automatisierung

### Übersicht
Eine automatische Pumpensteuerung sorgt für gleichmäßige Bewässerung ohne manuellen Aufwand. Das System steuert die Pumpe in festgelegten Intervallen und kann optional Sensoren zur Überwachung integrieren.

### ⚙️ Grundprinzip
Die Steuerung arbeitet mit einem Timer-basierten An/Aus-Zyklus:
- **Pumpe AN**: 15 Minuten (einstellbar)
- **Pumpe AUS**: 15 Minuten (einstellbar)
- Wiederholt sich automatisch 24/7

### 🔧 Benötigte Hardware

#### Basis-Version (Arduino)
- **Arduino Uno/Nano** (~15-25€)
- **5V Relais-Modul** (~3-5€) - zur Pumpensteuerung
- **Stromversorgung** 5V/1A für Arduino
- **Jumperkabel** für Verkabelung

#### Erweiterte Version (ESP32 mit WiFi)
- **ESP32 Development Board** (~8-15€)
- **5V Relais-Modul** (~3-5€)
- **DHT22 Sensor** (~5-8€) - optional für Temperatur/Luftfeuchtigkeit
- **Wasserstands-Sensor** (~3-5€) - optional
- **Stromversorgung** 5V/2A

### 📐 Verkabelung

#### Arduino/ESP32 → Relais
```
Arduino/ESP32    →    Relais-Modul
----------------------------------
5V/3.3V          →    VCC
GND              →    GND
Pin 7 (Arduino)  →    IN
Pin 26 (ESP32)   →    IN
```

#### Relais → Pumpe
```
Relais               Pumpe
----------------------
NO (Normal Open)  →  Pumpe 230V Phase
COM (Common)      →  230V Netz Phase
```

⚠️ **SICHERHEITSHINWEIS**: Arbeiten mit 230V sollten nur von Fachpersonen durchgeführt werden!

### 💾 Software-Lösungen

Zwei fertige Steuerungsprogramme sind im Repository verfügbar:

#### 1. **steuerung_arduino.ino** - Basis-Version
- ✅ Einfach und zuverlässig
- ✅ Timer-basierte Steuerung
- ✅ Serielle Ausgabe für Monitoring
- ✅ Optional: Wasserstands-Sensor Unterstützung
- ✅ Einstellbare Intervalle

**Empfohlene Einstellungen:**
- Junge Pflanzen: 10 min AN / 20 min AUS
- Etablierte Pflanzen: 15 min AN / 15 min AUS  
- Warmes Wetter: 15 min AN / 10 min AUS

#### 2. **steuerung_esp32_wifi.ino** - Erweiterte Version
- ✅ Alle Basis-Funktionen
- ✅ WiFi-Verbindung
- ✅ Web-Interface zur Überwachung
- ✅ Remote-Steuerung über Browser
- ✅ Temperatur & Luftfeuchtigkeit Anzeige
- ✅ Statistiken (Zyklen, Laufzeit)
- ✅ Manuelle Pumpensteuerung

**Web-Interface Features:**
- Echtzeit-Status der Pumpe
- Aktuelle Sensor-Werte
- Manuelle An/Aus-Schaltung
- Statistiken & Überwachung

### 🚀 Installation & Inbetriebnahme

#### Schritt 1: Arduino IDE installieren
1. Download von [arduino.cc/software](https://www.arduino.cc/en/software)
2. Arduino IDE installieren

#### Schritt 2: Board-Support hinzufügen
**Für ESP32:**
1. File → Preferences
2. Additional Boards Manager URLs: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Tools → Board → Boards Manager
4. "ESP32" suchen und installieren

#### Schritt 3: Bibliotheken installieren
**Für ESP32 WiFi-Version:**
1. Sketch → Include Library → Manage Libraries
2. Suchen und installieren:
   - "DHT sensor library" von Adafruit
   - "Adafruit Unified Sensor"

#### Schritt 4: Code anpassen
**Für ESP32 WiFi:**
```cpp
const char* ssid = "DEIN_WIFI_NAME";
const char* password = "DEIN_WIFI_PASSWORT";
```

**Intervalle anpassen (beide Versionen):**
```cpp
const unsigned long PUMP_ON_TIME = 15 * 60 * 1000;  // 15 Minuten
const unsigned long PUMP_OFF_TIME = 15 * 60 * 1000; // 15 Minuten
```

#### Schritt 5: Upload
1. Board auswählen: Tools → Board
2. Port auswählen: Tools → Port
3. Upload-Button klicken

#### Schritt 6: Testen
1. Serial Monitor öffnen (115200 baud für ESP32, 9600 für Arduino)
2. Status-Meldungen beobachten
3. **Für ESP32**: IP-Adresse notieren und im Browser öffnen

### 📊 Erweiterte Funktionen

#### Sensor-Integration
```cpp
// Wasserstands-Sensor
int waterLevel = analogRead(WATER_LEVEL_PIN);
if (waterLevel < WATER_LEVEL_MIN) {
  // Pumpe nicht starten bei zu wenig Wasser
}
```

#### Anpassung an Wetterbedingungen
```cpp
// Bei hohen Temperaturen kürzere Pausen
if (temperature > 28) {
  pumpOffTime = 10 * 60 * 1000;  // 10 Minuten Pause
} else {
  pumpOffTime = 15 * 60 * 1000;  // 15 Minuten Pause
}
```

### 🔍 Problemlösung

| Problem | Lösung |
|---------|--------|
| Pumpe läuft nicht | • Relais-Verkabelung prüfen<br>• Serielle Ausgabe kontrollieren<br>• Stromversorgung prüfen |
| WiFi verbindet nicht | • SSID/Passwort prüfen<br>• 2.4 GHz WiFi verwenden (nicht 5 GHz)<br>• Router-Nähe testen |
| Sensoren zeigen falsche Werte | • Verkabelung prüfen<br>• Sensor-Typ im Code kontrollieren<br>• Pull-up Widerstände bei Bedarf |
| System stürzt ab | • Stromversorgung verstärken<br>• Pumpe separat versorgen<br>• Relais-Modul prüfen |

### 🎯 Empfohlene Konfigurationen

#### Salat & Kräuter (Indoor)
```cpp
PUMP_ON_TIME  = 10 * 60 * 1000;  // 10 Min AN
PUMP_OFF_TIME = 20 * 60 * 1000;  // 20 Min AUS
```

#### Fruchtgemüse (Paprika, Gurke)
```cpp
PUMP_ON_TIME  = 15 * 60 * 1000;  // 15 Min AN
PUMP_OFF_TIME = 15 * 60 * 1000;  // 15 Min AUS
```

#### Outdoor im Sommer
```cpp
PUMP_ON_TIME  = 15 * 60 * 1000;  // 15 Min AN
PUMP_OFF_TIME = 10 * 60 * 1000;  // 10 Min AUS
```

### 💡 Zusätzliche Ideen

- **MQTT Integration**: Anbindung an Home Assistant oder andere Smart Home Systeme
- **Push-Benachrichtigungen**: Bei niedrigem Wasserstand
- **Datenlogging**: Aufzeichnung von Temperatur, Luftfeuchtigkeit, Laufzeiten
- **Zeitbasierte Steuerung**: Nur zu bestimmten Tageszeiten bewässern
- **pH/EC Messung**: Automatische Überwachung der Nährlösung

---
