# Troubleshooting Guide

## Bluetooth AppArmor Issue auf Ubuntu (Home Assistant)

### Problem

Wenn Sie Home Assistant auf Ubuntu (z.B. auf einem Mac Mini 2018 mit Ubuntu) verwenden und folgende Fehlermeldung erhalten:

```
Failed setup, will retry: hci0 (F0:18:98:87:AF:6F): hci0 (F0:18:98:87:AF:6F): Failed to start Bluetooth: [org.freedesktop.DBus.Error.AccessDenied] An AppArmor policy prevents this sender from sending this message to this recipient; type="method_call", sender="(null)" (inactive) interface="org.freedesktop.DBus" member="AddMatch" error name="(unset)" requested_reply="0" destination="org.freedesktop.DBus" (bus); Try power cycling the Bluetooth hardware.
```

### Ursache

AppArmor (Ubuntu's Sicherheitsmodul) blockiert die DBus-Kommunikation, die für Bluetooth erforderlich ist. Dies ist ein bekanntes Problem bei Home Assistant auf Ubuntu-Systemen.

### Lösung

#### Option 1: AppArmor-Profil für bluetoothd anpassen (Empfohlen)

1. Erstellen Sie ein lokales Override für das bluetoothd AppArmor-Profil:

```bash
sudo mkdir -p /etc/apparmor.d/local
sudo nano /etc/apparmor.d/local/usr.lib.bluetooth.bluetoothd
```

2. Fügen Sie folgende Zeilen hinzu:

```
# Allow DBus communication for Home Assistant
dbus send
    bus=system
    interface=org.freedesktop.DBus
    member=AddMatch
    peer=(name=org.freedesktop.DBus),

dbus send
    bus=system
    interface=org.freedesktop.DBus
    member=RemoveMatch
    peer=(name=org.freedesktop.DBus),

dbus send
    bus=system
    interface=org.freedesktop.DBus
    member=GetConnectionUnixUser
    peer=(name=org.freedesktop.DBus),
```

3. Fügen Sie diese Zeilen auch in die Haupt-AppArmor-Konfiguration ein:

```bash
sudo nano /etc/apparmor.d/usr.lib.bluetooth.bluetoothd
```

Suchen Sie nach der Zeile mit `#include <local/usr.lib.bluetooth.bluetoothd>` und stellen Sie sicher, dass sie vorhanden ist (normalerweise am Ende der Datei vor der schließenden Klammer `}`).

Falls die Datei nicht existiert oder anders heißt, können Sie versuchen:

```bash
sudo nano /etc/apparmor.d/usr.sbin.bluetoothd
```

4. Laden Sie das AppArmor-Profil neu:

```bash
sudo apparmor_parser -r /etc/apparmor.d/usr.lib.bluetooth.bluetoothd
# oder falls die Datei anders heißt:
sudo apparmor_parser -r /etc/apparmor.d/usr.sbin.bluetoothd
```

5. Starten Sie den Bluetooth-Dienst neu:

```bash
sudo systemctl restart bluetooth
```

6. Starten Sie Home Assistant neu.

#### Option 2: AppArmor temporär deaktivieren (Nicht empfohlen für Produktivumgebungen)

Falls Option 1 nicht funktioniert, können Sie AppArmor temporär deaktivieren, um zu testen, ob das Problem dadurch gelöst wird:

```bash
sudo systemctl stop apparmor
sudo systemctl disable apparmor
```

**Warnung:** Dies reduziert die Sicherheit Ihres Systems. Verwenden Sie diese Option nur zum Testen.

#### Option 3: Home Assistant Container/Supervisor Berechtigungen

Wenn Sie Home Assistant in einem Container oder als Supervised Installation ausführen:

1. Stellen Sie sicher, dass der Container die richtigen Berechtigungen hat:

```bash
# Für Docker:
docker run -d \
  --name homeassistant \
  --privileged \
  --network=host \
  -v /path/to/config:/config \
  -v /run/dbus:/run/dbus:ro \
  ghcr.io/home-assistant/home-assistant:stable
```

2. Der wichtige Teil ist `-v /run/dbus:/run/dbus:ro`, der den DBus-Socket in den Container einbindet.

#### Option 4: BlueZ Berechtigungen prüfen

Manchmal hilft es, die Berechtigungen für den Bluetooth-Adapter zu überprüfen:

```bash
sudo rfkill list
sudo rfkill unblock bluetooth
sudo hciconfig hci0 up
```

### Verifizierung

Nach der Implementierung einer Lösung:

1. Überprüfen Sie den Status des Bluetooth-Dienstes:

```bash
sudo systemctl status bluetooth
```

2. Überprüfen Sie, ob AppArmor-Einschränkungen bestehen:

```bash
sudo aa-status | grep bluetooth
```

3. Prüfen Sie die Home Assistant Logs auf weitere Bluetooth-Fehler.

### Weitere Hinweise

- Nach jedem Ubuntu-Update könnten die AppArmor-Profile zurückgesetzt werden. In diesem Fall müssen die Änderungen möglicherweise erneut angewendet werden.
- Die lokalen AppArmor-Overrides in `/etc/apparmor.d/local/` sollten Updates überstehen.
- Dokumentieren Sie alle vorgenommenen Änderungen für zukünftige Referenz.

### Zusätzliche Ressourcen

- [Home Assistant Bluetooth Integration](https://www.home-assistant.io/integrations/bluetooth/)
- [Ubuntu AppArmor Documentation](https://ubuntu.com/server/docs/security-apparmor)
- [BlueZ Documentation](http://www.bluez.org/)
