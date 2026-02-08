# 📐 Verkabelungs-Anleitung - Schritt für Schritt

## Basis-Setup: Arduino Uno + Relais + Pumpe

### Schritt 1: Material bereitstellen
```
✓ Arduino Uno oder Nano
✓ 5V Relais-Modul (1-Kanal)
✓ VIVOSUN Pumpe (oder ähnlich)
✓ Jumperkabel (3 Stück: Male-Female)
✓ USB-Kabel für Arduino
✓ 5V Netzteil (optional, für Dauerbetrieb)
```

---

## Verkabelung Arduino → Relais

### Schaltplan (Arduino Uno)
```
┌─────────────────┐
│   Arduino Uno   │
│                 │
│  5V  ────────┬──┼───► VCC (Relais)
│              │  │
│  GND ────────┼──┼───► GND (Relais)
│              │  │
│  Pin 7 ──────┼──┼───► IN  (Relais)
│              │  │
└──────────────┼──┘
               │
        (USB Stromversorgung)
```

### Detaillierte Anschlüsse

| Arduino Pin | Kabel-Farbe (Beispiel) | Relais Pin | Funktion |
|-------------|------------------------|------------|----------|
| 5V          | Rot                    | VCC        | Stromversorgung + |
| GND         | Schwarz                | GND        | Stromversorgung - |
| Pin 7 (D7)  | Gelb/Grün              | IN         | Steuersignal |

### Wichtig!
- ✅ VCC = Spannungsversorgung (Plus)
- ✅ GND = Ground (Masse/Minus)
- ✅ IN = Input Signal (Steuerung)
- ❌ **NICHT** VCC und GND vertauschen! (Relais kann kaputt gehen)

---

## Verkabelung Relais → Pumpe

### ⚠️ SICHERHEITSWARNUNG ⚠️
**Arbeiten mit 230V Netzspannung sind lebensgefährlich!**
- Nur durch Elektro-Fachpersonal
- Alle Geräte vom Netz trennen
- FI-Schutzschalter verwenden
- Bei Unsicherheit: Elektriker beauftragen

### Option A: Sichere Variante (Empfohlen für Anfänger)
Verwende eine geschaltete Steckdosenleiste:

```
230V Steckdose
    │
    ▼
┌─────────────────┐
│   Relais-Modul  │
│                 │
│  COM ◄───────── 230V Phase (von Steckdose)
│                 │
│  NO  ───────► Schuko-Buchse → Pumpe einstecken
│                 │
└─────────────────┘

Neutral + Erde: Direkt durchverbunden
```

**Vorteile:**
- ✅ Kein Schneiden von Kabeln
- ✅ Pumpe kann normal eingesteckt werden
- ✅ Einfach zu testen
- ✅ Flexibel

### Option B: Fest verdrahtet (für Fortgeschrittene)

```
230V Netzstecker
    │
    ├── Phase (L, Braun) ──────┐
    │                           │
    ├── Neutral (N, Blau) ─────┼──────► Pumpe (N)
    │                           │
    └── Erde (PE, Gelb-Grün) ──┼──────► Pumpe (PE)
                                │
                    ┌───────────┴─────────┐
                    │                     │
                    ▼                     │
                ┌─────────────────┐       │
                │   Relais        │       │
                │                 │       │
                │  COM ◄──────────┘       │
                │                         │
                │  NO  ────────────────────┼──► Pumpe (L)
                │                         │
                └─────────────────────────┘
```

### Relais Anschlüsse erklärt

| Relais Pin | Bedeutung | Verwendung |
|------------|-----------|------------|
| **COM** | Common (Gemeinsam) | 230V Eingang (Phase) |
| **NO** | Normally Open | Ausgang zur Pumpe (geschaltet) |
| **NC** | Normally Closed | **NICHT verwenden** |

**Wichtig**: 
- ✅ Verwende **NO** (Normally Open)
- ❌ **NICHT NC** verwenden (Pumpe läuft dauerhaft!)

### Wie funktioniert das Relais?

**Relais AUS (Arduino sendet kein Signal):**
```
COM ────X──── NO    (Kein Kontakt, Pumpe AUS)
```

**Relais AN (Arduino sendet 5V Signal):**
```
COM ────●──── NO    (Kontakt geschlossen, Pumpe AN)
        └─ Klick!
```

---

## ESP32 Version - Verkabelung

### Schaltplan ESP32 + Relais
```
┌─────────────────┐
│      ESP32      │
│                 │
│  3.3V ───────┬──┼───► VCC (Relais 3.3V kompatibel)
│  oder        │  │     ODER externes 5V
│  5V  ────────┘  │
│                 │
│  GND ────────┬──┼───► GND (Relais)
│              │  │
│  GPIO 26 ────┼──┼───► IN  (Relais)
│              │  │
└──────────────┼──┘
               │
        (USB Stromversorgung)
```

### ESP32 Pin-Belegung

| ESP32 Pin | Relais Pin | Funktion |
|-----------|------------|----------|
| 3.3V      | VCC        | Wenn Relais 3.3V-kompatibel |
| 5V        | VCC        | Wenn Relais 5V benötigt |
| GND       | GND        | Masse |
| GPIO 26   | IN         | Steuersignal |

**Hinweis**: Viele Relais benötigen 5V. Bei ESP32 kann externes 5V-Netzteil nötig sein.

### ESP32 + DHT22 Sensor (optional)

```
┌─────────────────┐              ┌─────────────┐
│      ESP32      │              │    DHT22    │
│                 │              │             │
│  3.3V ──────────┼──────────────┼► Pin 1 (VCC)│
│                 │              │             │
│  GND ───────────┼──────────────┼► Pin 4 (GND)│
│                 │              │             │
│  GPIO 4 ────────┼──────────────┼► Pin 2 (DATA)
│                 │              │             │
└─────────────────┘              └─────────────┘
                                       │
                                       ├── 10kΩ Widerstand (Pull-up)
                                       │   von Pin 2 zu Pin 1
```

### DHT22 Pin-Belegung
```
DHT22 Sensor (Vorderansicht):
┌─────────────┐
│  │  │  │  │ │
│  1  2  3  4 │
└─────────────┘

Pin 1: VCC (+3.3V oder +5V)
Pin 2: DATA (zu GPIO 4)
Pin 3: Nicht belegt
Pin 4: GND
```

---

## Komplettes System mit allen Sensoren

### Vollausbau ESP32
```
                    ┌─────────────────┐
                    │      ESP32      │
                    │                 │
    DHT22           │  GPIO 4 ◄────── DHT22 Sensor
    (Temp/Hum)      │                 │
                    │  GPIO 26 ────── Relais (Pumpe)
    Relais          │                 │
    (Pumpe)         │  GPIO 34 ◄────── Wasserstands-Sensor
                    │  (ADC)          │
    Wasser-         │                 │
    stand           │  3.3V ──────┬── VCC (Sensoren)
                    │             │   │
                    │  GND ───────┼── GND (Sensoren)
                    │             │   │
                    └─────────────┼───┘
                                  │
                          (Gemeinsame Versorgung)
```

---

## Stromversorgung

### Option 1: USB-Netzteil (einfach)
```
USB-Netzteil (5V/1A) → Micro-USB → Arduino/ESP32
```
- ✅ Einfach
- ✅ Günstig
- ❌ Nur für Arduino + Relais (ohne starke Sensoren)

### Option 2: Externes Netzteil (empfohlen)
```
Netzteil 5V/2A
    │
    ├── VCC → Arduino/ESP32 5V Pin
    │
    └── GND → Arduino/ESP32 GND Pin
```
- ✅ Stabil
- ✅ Genug Leistung für Sensoren
- ✅ Professioneller

### Option 3: Powerbank (mobil)
```
USB-Powerbank (10000mAh) → Arduino/ESP32
```
- ✅ Batteriebetrieb möglich
- ✅ Gut für Tests
- ❌ Muss regelmäßig geladen werden
- **Haltbarkeit**: ~2-4 Tage je nach Powerbank

---

## Kabel-Farben (Standard)

### Elektronik (Niedervolt)
| Farbe | Funktion |
|-------|----------|
| **Rot** | Plus/VCC (+5V, +3.3V) |
| **Schwarz** | Minus/GND |
| **Gelb/Grün/Weiß** | Signal/Daten |

### 230V Netzspannung
| Farbe | Funktion | Wichtigkeit |
|-------|----------|-------------|
| **Braun** | Phase (L) | ⚡ Gefährlich! |
| **Blau** | Neutral (N) | Rückleiter |
| **Gelb-Grün** | Erde (PE) | Sicherheit |

---

## Gehäuse-Montage

### Empfohlener Aufbau
```
┌────────────────────────────────┐
│  Wasserdichtes Gehäuse         │
│  (IP54 oder besser)            │
│                                │
│  ┌──────────┐  ┌───────────┐  │
│  │ Arduino/ │  │  Relais   │  │
│  │  ESP32   │  │  Modul    │  │
│  └──────────┘  └───────────┘  │
│                                │
│  [USB Port]    [Kabel-Ausgang]│
└────────────────────────────────┘
         │               │
         │               └─► Zur Pumpe (230V)
         │
         └─► USB Netzteil
```

### Kabel-Durchführungen
- **Kabelverschraubungen** (M12/M16) verwenden
- Wasserdicht abdichten
- Zugentlastung beachten

### Montage-Tipps
1. ✅ Gehäuse über Wasseroberfläche montieren
2. ✅ Kabel nach unten führen (Tropfschlaufe)
3. ✅ Belüftung vorsehen (gegen Kondenswasser)
4. ✅ Beschriftung anbringen

---

## Schritt-für-Schritt Anleitung (Anfänger)

### Phase 1: Vorbereitung (15 Minuten)
1. ☐ Alle Komponenten bereitlegen
2. ☐ Arbeitsplatz vorbereiten
3. ☐ Code auf Computer laden
4. ☐ Arduino IDE öffnen

### Phase 2: Verkabelung (20 Minuten)
1. ☐ Arduino/ESP32 auf Tisch legen
2. ☐ Relais daneben legen
3. ☐ **VCC** Kabel: 5V → VCC (Relais) - **ROT**
4. ☐ **GND** Kabel: GND → GND (Relais) - **SCHWARZ**
5. ☐ **Signal** Kabel: Pin 7 → IN (Relais) - **GELB**
6. ☐ Alle Verbindungen prüfen

### Phase 3: Software (10 Minuten)
1. ☐ Arduino per USB verbinden
2. ☐ Code in Arduino IDE öffnen
3. ☐ Board auswählen (Tools → Board)
4. ☐ Port auswählen (Tools → Port)
5. ☐ Code hochladen (Upload Button)
6. ☐ Serial Monitor öffnen (9600 baud)

### Phase 4: Test ohne Pumpe (5 Minuten)
1. ☐ Serial Monitor beobachten
2. ☐ Meldung "Pumpe AN" → Relais sollte klicken ✓
3. ☐ LED am Relais leuchtet ✓
4. ☐ Meldung "Pumpe AUS" → Relais klickt zurück ✓

### Phase 5: Pumpe anschließen (10 Minuten)
**NUR wenn Test Phase 4 erfolgreich!**

⚠️ **STROM AUS vor Verkabelung!**

1. ☐ Arduino vom Strom trennen
2. ☐ Pumpe vom Strom trennen
3. ☐ Relais COM → 230V Phase
4. ☐ Relais NO → Pumpe Phase
5. ☐ Neutral & Erde direkt verbinden
6. ☐ **ALLE Verbindungen isolieren!**
7. ☐ Sichtprüfung

### Phase 6: Finaler Test (5 Minuten)
1. ☐ System einschalten
2. ☐ Serial Monitor beobachten
3. ☐ Bei "Pumpe AN" → Pumpe läuft ✓
4. ☐ Bei "Pumpe AUS" → Pumpe stoppt ✓
5. ☐ 2-3 Zyklen beobachten
6. ☐ Alles OK → **Fertig!** 🎉

---

## Troubleshooting Verkabelung

| Problem | Wahrscheinliche Ursache | Lösung |
|---------|------------------------|---------|
| Relais klickt nicht | • Kein Strom am Relais<br>• Falsche Verkabelung<br>• Defektes Relais | • VCC/GND prüfen<br>• Kabel tauschen<br>• Relais testen |
| Relais klickt, Pumpe läuft nicht | • NC statt NO verwendet<br>• 230V Verkabelung falsch | • NO Pin verwenden<br>• Verkabelung prüfen |
| Pumpe läuft dauerhaft | • NC statt NO<br>• Code-Problem | • Auf NO wechseln<br>• Serial Monitor prüfen |
| Arduino startet nicht | • Zu wenig Strom<br>• Kurzschluss | • Stärkeres Netzteil<br>• Verkabelung prüfen |

---

## Checkliste vor Dauerbetrieb

☐ Code läuft stabil (min. 24h Testlauf)  
☐ Alle Lötstellen/Verbindungen sicher  
☐ 230V Verkabelung professionell isoliert  
☐ Gehäuse wasserdicht und sicher montiert  
☐ FI-Schutzschalter vorhanden  
☐ Überwachung eingerichtet (Serial/WiFi)  
☐ Notfall-Plan vorhanden  

---

## Sicherheits-Endkontrolle

✅ **Vor Inbetriebnahme prüfen:**

1. [ ] Keine blanken 230V Kontakte zugänglich
2. [ ] Alle Schrauben fest angezogen
3. [ ] Kein Wasser kann in Elektronik gelangen
4. [ ] Relais schaltet korrekt (Test durchgeführt)
5. [ ] Pumpe funktioniert im Zyklus
6. [ ] Kabel ordentlich verlegt (keine Stolperfalle)
7. [ ] Beschriftung angebracht ("230V! Vorsicht!")
8. [ ] Zweite Person hat Setup geprüft

---

**Bei Zweifeln: Elektriker konsultieren!**

Es ist besser, einmal professionelle Hilfe zu holen, als ein Sicherheitsrisiko einzugehen.
