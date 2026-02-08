# 🚀 Quick Start - Automatische Pumpensteuerung in 30 Minuten

Diese Anleitung führt dich Schritt für Schritt zur funktionierenden automatischen Pumpensteuerung.

---

## ⏱️ Zeitplan

- **15 Min**: Einkaufen/Komponenten bereitstellen
- **10 Min**: Software installieren & Code hochladen  
- **5 Min**: Verkabelung
- **5 Min**: Test

**Gesamt: ~30-35 Minuten**

---

## 📋 Was du brauchst

### Minimale Variante (~30€)
- [ ] **Arduino Nano** (oder Uno) - ~10€
- [ ] **5V Relais-Modul** (1-Kanal) - ~4€
- [ ] **USB-Kabel** (passend für Arduino) - ~3€
- [ ] **3x Jumperkabel** (Female-Male oder Male-Male) - ~3€
- [ ] **USB-Netzteil** 5V/1A - ~8€
- [ ] Deine **VIVOSUN Pumpe** (bereits vorhanden)

### Optional
- [ ] **Wasserstands-Sensor** - ~4€
- [ ] **Gehäuse** (wasserdicht) - ~10€

---

## 🔧 Schritt 1: Software Installation (10 Min)

### 1.1 Arduino IDE herunterladen
1. Öffne: https://www.arduino.cc/en/software
2. Download für dein Betriebssystem (Windows/Mac/Linux)
3. Installation durchführen
4. Arduino IDE starten

### 1.2 Code herunterladen
1. Öffne: https://github.com/mikagorka/hydroponic_tower
2. Download `steuerung_arduino.ino`
3. Doppelklick auf die Datei → Öffnet Arduino IDE

**Oder:** Code manuell kopieren
```
1. Arduino IDE → Neues Projekt
2. Code aus steuerung_arduino.ino kopieren
3. Einfügen in Arduino IDE
```

### 1.3 Code anpassen (Optional)
Im Code findest du diese Zeilen (ca. Zeile 22-23):
```cpp
const unsigned long PUMP_ON_TIME = 15 * 60 * 1000;  // 15 Min AN
const unsigned long PUMP_OFF_TIME = 15 * 60 * 1000; // 15 Min AUS
```

**Empfohlene Einstellungen:**
- Junge Pflanzen: `10` Min AN, `20` Min AUS
- Normale Pflanzen: `15` Min AN, `15` Min AUS
- Warmes Wetter: `15` Min AN, `10` Min AUS

**Für jetzt**: Lass es bei 15/15 Minuten!

### 1.4 Hochladen zum Arduino
1. **Arduino per USB verbinden**
2. Tools → Board → Arduino Uno (oder Nano)
3. Tools → Port → Wähle den Port (meist nur einer sichtbar)
4. **Upload-Button klicken** (→ Pfeil-Symbol)
5. Warten bis "Upload abgeschlossen" erscheint

**Häufige Fehler:**
- Port nicht sichtbar? → USB-Kabel wechseln
- Upload-Fehler? → Richtiges Board gewählt?

---

## 🔌 Schritt 2: Verkabelung (5 Min)

### 2.1 Material bereitlegen
```
Arduino Nano/Uno
Relais-Modul
3x Jumperkabel
```

### 2.2 Verbindungen herstellen

**Verbindung 1**: Arduino **5V** → Relais **VCC** (Rotes Kabel)  
**Verbindung 2**: Arduino **GND** → Relais **GND** (Schwarzes Kabel)  
**Verbindung 3**: Arduino **Pin 7** → Relais **IN** (Gelbes/Grünes Kabel)

```
Arduino              Relais
-------              ------
  5V  ────────────► VCC
  GND ────────────► GND
  Pin 7 ──────────► IN
```

### 2.3 Visueller Check
- [ ] Alle 3 Kabel verbunden?
- [ ] Richtige Pins (5V, GND, Pin 7)?
- [ ] Kabel fest eingesteckt?

---

## ✅ Schritt 3: Erster Test (ohne Pumpe) (3 Min)

### 3.1 Serial Monitor öffnen
1. Arduino IDE: Tools → Serial Monitor
2. Unten rechts: **9600 baud** einstellen
3. Du solltest sehen:
```
=================================
Hydroponik Tower Steuerung v1.0
=================================
System initialisiert
Pumpe AN Zeit: 15 Minuten
Pumpe AUS Zeit: 15 Minuten
```

### 3.2 Relais-Test beobachten
**Nach kurzer Zeit:**
```
>>> PUMPE EINGESCHALTET <<<
```
→ **Relais sollte KLICKEN** ✓  
→ **LED am Relais leuchtet** ✓

**Nach 15 Minuten (oder eingestellte Zeit):**
```
>>> PUMPE AUSGESCHALTET <<<
```
→ **Relais klickt zurück** ✓  
→ **LED am Relais aus** ✓

**Funktioniert nicht?** → Siehe [Problemlösung](#problemlösung)

---

## 🚰 Schritt 4: Pumpe anschließen (5 Min)

### ⚠️ WICHTIGER SICHERHEITSHINWEIS
**Arbeiten mit 230V Netzspannung sind gefährlich!**
- Bei Unsicherheit → Elektriker beauftragen
- Immer Strom aus vor Verkabelung
- FI-Schutzschalter verwenden

### Empfohlener sicherer Aufbau (für Anfänger)

**Material zusätzlich:**
- Schuko-Steckdose (Einbau-Dose) ~3€
- Oder: Verlängerungskabel zum Aufschneiden ~5€

**Aufbau:**
```
230V Steckdose → Relais COM
Relais NO → Steckdosen-Buchse → Pumpe einstecken
```

### Alternative: Mechanische Zeitschaltuhr
Falls die 230V Verkabelung zu kompliziert ist:
- Kaufe mechanische Zeitschaltuhr (~10€)
- Stelle 15 Min AN / 15 Min AUS ein
- Arduino überwacht dann nur, steuert aber nicht direkt
- **Oder:** Nutze Arduino nur für Monitoring/Sensoren

---

## 🎯 Schritt 5: Finaler Test (2 Min)

### 5.1 Komplett-Check
1. [ ] Arduino ist mit USB verbunden
2. [ ] Relais ist korrekt verkabelt
3. [ ] Pumpe ist angeschlossen (oder Zeitschaltuhr)
4. [ ] Serial Monitor zeigt Meldungen

### 5.2 Beobachten
- Warte auf ">>> PUMPE EINGESCHALTET <<<"
- Pumpe sollte laufen
- Nach eingestellter Zeit wieder stoppen

### 5.3 Fertig! 🎉
**Glückwunsch!** Dein Hydroponik-Tower ist jetzt automatisiert!

---

## 📊 Monitoring (Optional)

### Während des Betriebs
Lasse Arduino IDE offen mit Serial Monitor:
- Siehst du Echtzeit-Status
- Erkennst du Probleme sofort
- Kannst du Zeiten anpassen

### Dauerbetrieb
- Arduino kann USB-verbunden bleiben
- **Oder**: Nutze externes 5V Netzteil
- Serial Monitor optional (nur für Debugging)

---

## ⚙️ Einstellungen anpassen

### Intervalle ändern

**Im Code ändern (Zeile 22-23):**
```cpp
// Beispiel: 10 Min AN, 20 Min AUS
const unsigned long PUMP_ON_TIME = 10 * 60 * 1000;
const unsigned long PUMP_OFF_TIME = 20 * 60 * 1000;
```

**Nach Änderung:**
1. Speichern (Strg+S / Cmd+S)
2. Upload-Button klicken
3. Fertig!

### Wasserstands-Sensor hinzufügen

**Code ist bereits vorbereitet!**

1. Wasserstands-Sensor an **A0** anschließen
2. Sensor in Wassertank tauchen
3. Code bereits aktiv - Pumpe stoppt bei zu wenig Wasser

---

## 🆙 Upgrade auf ESP32 mit WiFi

**Später upgraden möglich:**
1. ESP32 Board kaufen (~12€)
2. Verkabelung ähnlich wie Arduino
3. `steuerung_esp32_wifi.ino` hochladen
4. WiFi-Zugangsdaten eingeben
5. Web-Interface im Browser öffnen

**Vorteile:**
- ✅ Steuerung vom Handy/PC
- ✅ Überwachung ohne USB
- ✅ Temperatur-Anzeige
- ✅ Statistiken

---

## 📱 Alternative: Mechanische Zeitschaltuhr

**Wenn Elektronik zu kompliziert ist:**

### Option A: Analog-Zeitschaltuhr
```
Kosten: ~10€
Setup: 2 Minuten
```
1. Zeitschaltuhr in Steckdose
2. Pumpe in Zeitschaltuhr
3. Segmente für AN-Zeiten drücken (z.B. jede halbe Stunde 15 Min)
4. Fertig!

**Vorteile:**
- ✅ Super einfach
- ✅ Sehr zuverlässig
- ✅ Keine Programmierung

**Nachteile:**
- ❌ Keine Sensoren
- ❌ Feste Zeiten
- ❌ Kein Monitoring

### Option B: Digital-Zeitschaltuhr
```
Kosten: ~15€
Setup: 5 Minuten
```
- Genauere Zeiteinstellung
- Mehrere Programme
- Wochentage-Steuerung

---

## 🐛 Problemlösung

### Arduino wird nicht erkannt
**Windows:**
1. Geräte-Manager öffnen
2. Suche nach "USB-Serial"
3. Treiber aktualisieren
4. CH340 Treiber installieren (Google: "CH340 Treiber")

**Mac:**
1. System-Einstellungen → Sicherheit
2. Erlaube "System Extension"
3. Neustart

### Relais klickt nicht
1. [ ] Stromversorgung OK? (LED an Arduino leuchtet?)
2. [ ] Kabel richtig verbunden?
3. [ ] Code hochgeladen?
4. [ ] Serial Monitor zeigt "PUMPE EINGESCHALTET"?

**Test:** 
- Tausche Kabel von Pin 7 auf Pin 13
- Ändere im Code `const int RELAY_PIN = 7;` zu `= 13;`
- Upload → Wenn jetzt klappt, war Pin 7 defekt

### Pumpe läuft dauerhaft
- **Ursache**: Vermutlich NC statt NO am Relais
- **Lösung**: Umstecken auf NO Pin

### Upload-Fehler in Arduino IDE
```
Error: avrdude: stk500_recv(): programmer is not responding
```
**Lösung:**
1. Anderes USB-Kabel probieren
2. Anderen USB-Port probieren  
3. Arduino-Board im Menü korrekt?
4. Richtiger Port gewählt?

---

## 📚 Weiterführende Dokumentation

Für Details siehe:
- **README.md** - Vollständige Dokumentation
- **VERKABELUNG.md** - Detaillierte Schaltpläne
- **FAQ.md** - Häufige Fragen
- **EINKAUFSLISTE.md** - Komponenten-Links

---

## 💡 Tipps für beste Ergebnisse

### Bewässerungs-Optimierung
1. **Starte mit 15/15 Min** (AN/AUS)
2. **Beobachte Pflanzen 3-4 Tage**
3. **Anpassen nach Bedarf:**
   - Pflanzen welken → Mehr Wasser (länger AN oder kürzer AUS)
   - Zu nass/gelb → Weniger Wasser

### System-Stabilität
- ✅ Verwende qualitatives USB-Netzteil
- ✅ Kurze Kabel zum Relais
- ✅ Relais mit Optokoppler
- ✅ Elektronik trocken halten

### Wartung
- 1x pro Woche: Visueller Check
- 1x pro Monat: Sensoren reinigen
- Bei Problemen: Serial Monitor prüfen

---

## 🎓 Nächste Schritte

### Level 1: Basis (Du bist hier!)
- [x] Arduino Setup
- [x] Relais-Steuerung
- [x] Automatische Bewässerung

### Level 2: Sensoren
- [ ] Wasserstands-Sensor hinzufügen
- [ ] Temperatur überwachen
- [ ] Automatische Anpassungen

### Level 3: WiFi & Web
- [ ] Upgrade auf ESP32
- [ ] Web-Interface nutzen
- [ ] Remote-Steuerung

### Level 4: Smart Home
- [ ] MQTT Integration
- [ ] Home Assistant
- [ ] Alexa/Google Home

---

## ❓ Hilfe bekommen

**Probleme?**
1. Prüfe [FAQ.md](FAQ.md)
2. Schaue in [VERKABELUNG.md](VERKABELUNG.md)
3. YouTube: "Arduino Tutorial Deutsch"
4. Arduino Forum (deutsch)

**Code funktioniert nicht?**
- Screenshot vom Serial Monitor machen
- GitHub Issue öffnen
- Community fragen

---

## ✅ Erfolg Checkliste

- [ ] Arduino IDE installiert
- [ ] Code hochgeladen
- [ ] Relais klickt im Takt
- [ ] Pumpe schaltet automatisch
- [ ] System läuft stabil
- [ ] **Pflanzen wachsen!** 🌱

---

**Viel Erfolg mit deinem automatisierten Hydroponik-Tower! 🚀**

Bei Fragen: GitHub Issues öffnen oder Community fragen.
