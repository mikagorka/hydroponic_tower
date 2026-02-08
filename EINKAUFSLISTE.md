# 🛒 Einkaufsliste - Automatisierung Komponenten

## Basis-Version mit Arduino Uno/Nano

### Elektronik
| Komponente | Beschreibung | Ungefährer Preis | Link/Hinweise |
|------------|--------------|------------------|---------------|
| Arduino Uno oder Nano | Microcontroller Board | 15-25€ | Original oder kompatibel |
| 5V Relais-Modul | 1-Kanal Relais 5V | 3-5€ | Mit Optokoppler bevorzugt |
| USB-Kabel | Typ A zu Typ B (Uno) oder Mini-USB (Nano) | 3-5€ | Für Programmierung & Stromversorgung |
| Jumperkabel | Male-Female & Male-Male | 5-8€ | Set mit verschiedenen Längen |
| Steckbrett | Optional für Prototyping | 3-5€ | 400 oder 830 Kontakte |

**Gesamt: ca. 30-50€**

---

## Erweiterte Version mit ESP32 + WiFi

### Elektronik
| Komponente | Beschreibung | Ungefährer Preis | Link/Hinweise |
|------------|--------------|------------------|---------------|
| ESP32 Development Board | Mit WiFi & Bluetooth | 8-15€ | NodeMCU-32S oder ähnlich |
| 5V Relais-Modul | 1-Kanal Relais (3.3V oder 5V) | 3-5€ | Mit Optokoppler |
| DHT22 Sensor | Temperatur & Luftfeuchtigkeit | 5-8€ | AM2302 Sensor |
| Wasserstands-Sensor | Analog oder digital | 3-5€ | Optional |
| Micro-USB Kabel | Für ESP32 | 3-5€ | Für Programmierung & Stromversorgung |
| Jumperkabel | Male-Female & Male-Male | 5-8€ | Set mit verschiedenen Längen |
| Netzteil 5V/2A | Stabile Stromversorgung | 8-12€ | USB-Netzteil oder DC-Adapter |

**Gesamt: ca. 40-65€**

---

## Zusätzliche optionale Komponenten

### Sensoren & Monitoring
| Komponente | Beschreibung | Ungefährer Preis | Zweck |
|------------|--------------|------------------|-------|
| pH-Sensor | Analog pH-Sensor Modul | 15-30€ | Nährlösung-Überwachung |
| EC/TDS-Sensor | Leitfähigkeits-Sensor | 8-15€ | Nährstoffkonzentration |
| Ultraschall-Sensor | HC-SR04 Wasserstands-Messung | 3-5€ | Präzise Füllstandsmessung |
| DS18B20 | Wasserdichte Temp.-Sonde | 5-8€ | Wassertemperatur |
| OLED Display | 0.96" 128x64 | 5-8€ | Lokale Anzeige |

### Gehäuse & Montage
| Komponente | Beschreibung | Ungefährer Preis | Zweck |
|------------|--------------|------------------|-------|
| Wasserdichtes Gehäuse | IP65 Kunststoff-Box | 8-15€ | Schutz der Elektronik |
| DIN-Rail Halterung | Für Gehäuse-Montage | 3-5€ | Professionelle Installation |
| Kabelverschraubungen | M12 oder M16 | 2-3€/Stück | Wasserdichte Kabelführung |
| Lüsterklemmen | Für 230V Verbindungen | 5-10€ | Sichere Verkabelung |

### Stromversorgung
| Komponente | Beschreibung | Ungefährer Preis | Zweck |
|------------|--------------|------------------|-------|
| Step-Down Wandler | 12V/24V zu 5V | 3-5€ | Falls andere Spannungsquelle |
| USV / Powerbank | Backup Stromversorgung | 15-50€ | Schutz vor Stromausfall |
| Schuko-Steckdose | Mit Schalter | 3-5€ | Einfache Pumpen-Integration |

---

## Werkzeug (falls nicht vorhanden)

| Werkzeug | Zweck | Ungefährer Preis |
|----------|-------|------------------|
| Abisolierzange | Kabel abisolieren | 8-15€ |
| Seitenschneider | Kabel schneiden | 5-10€ |
| Schraubendreher-Set | Montage | 10-20€ |
| Multimeter | Spannungsprüfung | 10-25€ |
| Lötkolben | Falls Löten nötig | 15-30€ |
| Heißklebepistole | Fixierung | 8-15€ |

---

## Empfohlene Shops (Deutschland)

### Online-Shops für Elektronik
- **Amazon.de** - Schnelle Lieferung, breite Auswahl
- **Conrad.de** - Hochwertige Komponenten, guter Service
- **Reichelt.de** - Große Auswahl, Fachhandel
- **AZ-Delivery** (Amazon) - ESP32 & Arduino Komponenten
- **Berrybase.de** - Raspberry Pi & Maker-Elektronik
- **Pollin.de** - Günstige Elektronik-Bauteile
- **Eckstein-Shop.de** - Mikrocontroller & Module

### Alternative: China-Import (längere Lieferzeit)
- **AliExpress** - Sehr günstig, 2-4 Wochen Lieferzeit
- **Banggood** - Ähnlich wie AliExpress

---

## Starter-Kits

### Empfehlung 1: Komplettes Arduino Starter Kit
- **AZ-Delivery** Arduino Nano + Relais + Sensoren Set
- ca. 25-35€
- Enthält: Arduino Nano, Relais, Jumperkabel, Breadboard

### Empfehlung 2: ESP32 Development Kit
- **AZ-Delivery** ESP32 Dev Kit mit Sensoren
- ca. 30-45€  
- Enthält: ESP32, DHT22, Relais, Kabel, Breadboard

---

## Sicherheitshinweise

⚠️ **WICHTIG bei 230V Arbeiten:**
- Nur durch qualifizierte Personen
- Immer Netzstecker ziehen vor Arbeiten
- Berührungsschutz sicherstellen
- FI-Schutzschalter verwenden
- Bei Unsicherheit: Elektriker beauftragen

---

## Quick-Start Empfehlung

### Minimaler Einstieg (35€)
```
✓ Arduino Nano Clone (10€)
✓ 5V Relais Modul (4€)
✓ USB-Kabel (3€)
✓ Jumperkabel Set (5€)
✓ Breadboard (3€)
✓ Netzteil 5V/1A (10€)
```

### Komfort-Version (60€)
```
✓ ESP32 Development Board (12€)
✓ 5V Relais Modul mit Optokoppler (5€)
✓ DHT22 Temperatur/Luftfeuchte (7€)
✓ Wasserstands-Sensor (4€)
✓ Jumper-Kabel Set (6€)
✓ Wasserdichtes Gehäuse (12€)
✓ Netzteil 5V/2A (12€)
✓ Kabel & Kleinteile (2€)
```

---

## Hinweise zur Bestellung

1. **Sets bevorzugen**: Arduino/ESP32 Starter Kits sind oft günstiger
2. **Versandkosten beachten**: Größere Sammelbestellung spart Geld
3. **Qualität**: Bei Netzteilen und Relais nicht am falschen Ende sparen
4. **Kompatibilität prüfen**: ESP32 benötigt 3.3V-kompatible Sensoren oder Level-Shifter
5. **Ersatzteile**: 1-2 Relais und Sensoren als Reserve bestellen

---

## Support & Community

Bei Fragen zur Hardware:
- Arduino Forum: [forum.arduino.cc](https://forum.arduino.cc)
- ESP32 Forum: [esp32.com](https://esp32.com)
- Reddit: r/arduino, r/esp32
- YouTube: Viele deutschsprachige Tutorials verfügbar
