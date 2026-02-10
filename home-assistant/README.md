# Home Assistant Bluetooth/DBus Fix für Ubuntu

Diese Anleitung hilft bei der Behebung des folgenden Fehlers in Home Assistant auf Ubuntu-Systemen:

```
Failed setup, will retry: hci0 (F0:18:98:87:AF:6F): hci0 (F0:18:98:87:AF:6F): Failed to start Bluetooth: [org.freedesktop.DBus.Error.AccessDenied] An AppArmor policy prevents this sender from sending this message to this recipient; type="method_call", sender="(null)" (inactive) interface="org.freedesktop.DBus" member="AddMatch" error name="(unset)" requested_reply="0" destination="org.freedesktop.DBus" (bus); Try power cycling the Bluetooth hardware.
```

## 🔍 Problem

AppArmor blockiert die DBus-Kommunikation zwischen Home Assistant und dem Bluetooth-Dienst. Dies verhindert, dass Home Assistant auf Bluetooth-Hardware zugreifen kann.

## ✅ Lösung

Die Lösung besteht darin, ein AppArmor-Profil zu erstellen, das Home Assistant explizit die erforderlichen DBus-Berechtigungen für Bluetooth erteilt.

## 📋 Voraussetzungen

- Ubuntu-System mit Home Assistant installiert
- Root/sudo-Zugriff
- AppArmor aktiviert (Standard auf Ubuntu)

## 🚀 Installation

### Automatische Installation (empfohlen)

1. **Navigieren Sie zum home-assistant Verzeichnis:**
   ```bash
   cd home-assistant
   ```

2. **Führen Sie das Setup-Skript aus:**
   ```bash
   sudo bash setup-bluetooth-fix.sh
   ```

3. **Starten Sie Home Assistant neu:**
   ```bash
   sudo systemctl restart home-assistant@homeassistant
   ```

### Manuelle Installation

1. **Kopieren Sie das AppArmor-Profil:**
   ```bash
   sudo cp apparmor.d/usr.bin.homeassistant /etc/apparmor.d/
   sudo chmod 644 /etc/apparmor.d/usr.bin.homeassistant
   ```

2. **Laden Sie das Profil:**
   ```bash
   sudo apparmor_parser -r /etc/apparmor.d/usr.bin.homeassistant
   ```

3. **Starten Sie Bluetooth neu:**
   ```bash
   sudo systemctl restart bluetooth
   ```

4. **Starten Sie Home Assistant neu:**
   ```bash
   sudo systemctl restart home-assistant@homeassistant
   ```

## 🔧 Fehlerbehebung

### Überprüfen Sie die Home Assistant Logs

```bash
journalctl -u home-assistant@homeassistant -f
```

### Überprüfen Sie AppArmor-Blockierungen

```bash
sudo dmesg | grep -i apparmor | tail -20
```

### Überprüfen Sie den Bluetooth-Status

```bash
systemctl status bluetooth
hciconfig
```

### Testen Sie die DBus-Verbindung

```bash
dbus-send --system --print-reply --dest=org.bluez / org.freedesktop.DBus.Introspectable.Introspect
```

### AppArmor im Complain-Modus (für Debugging)

Wenn Sie weiterhin Probleme haben, können Sie AppArmor vorübergehend in den "Complain"-Modus versetzen:

```bash
sudo aa-complain /etc/apparmor.d/usr.bin.homeassistant
```

Dies protokolliert Verstöße, blockiert aber nicht. Zum Reaktivieren:

```bash
sudo aa-enforce /etc/apparmor.d/usr.bin.homeassistant
```

### Alternative: AppArmor für Home Assistant deaktivieren

**⚠️ Nur als letztes Mittel:**

```bash
sudo ln -s /etc/apparmor.d/usr.bin.homeassistant /etc/apparmor.d/disable/
sudo apparmor_parser -R /etc/apparmor.d/usr.bin.homeassistant
```

## 📝 Was macht das AppArmor-Profil?

Das Profil erlaubt Home Assistant:

- **DBus-Kommunikation** auf System- und Session-Bus
- **Bluetooth-spezifische DBus-Schnittstellen** (org.bluez.*)
- **DBus-Operationen** wie AddMatch, RemoveMatch, GetNameOwner
- **Zugriff auf Bluetooth-Hardware** (/sys/class/bluetooth, /dev/rfkill)
- **Netzwerkzugriff** für Home Assistant-Funktionen
- **Zugriff auf Home Assistant-Konfiguration** und temporäre Dateien

## 🔒 Sicherheitshinweise

- Das Profil folgt dem Prinzip der minimalen Rechte (least privilege)
- Es erlaubt nur spezifische DBus-Operationen, die für Bluetooth erforderlich sind
- Netzwerk- und Dateizugriffe sind auf notwendige Pfade beschränkt

## 🆘 Weitere Hilfe

Falls der Fehler weiterhin besteht:

1. Überprüfen Sie, ob Home Assistant unter einem anderen Binärpfad läuft
2. Passen Sie den Pfad in `/etc/apparmor.d/usr.bin.homeassistant` an
3. Prüfen Sie die Bluetooth-Hardware: `rfkill list`
4. Stellen Sie sicher, dass der Benutzer in der Gruppe `bluetooth` ist:
   ```bash
   sudo usermod -a -G bluetooth homeassistant
   ```

## 📚 Zusätzliche Ressourcen

- [AppArmor Documentation](https://gitlab.com/apparmor/apparmor/-/wikis/Documentation)
- [Home Assistant Bluetooth Integration](https://www.home-assistant.io/integrations/bluetooth/)
- [DBus Documentation](https://www.freedesktop.org/wiki/Software/dbus/)
