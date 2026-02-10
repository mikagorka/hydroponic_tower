# Configuration Files

This directory contains configuration files to help resolve common issues when integrating Home Assistant with the hydroponic tower system.

## Files

### `apparmor-bluetooth-fix`

AppArmor configuration override to fix Bluetooth DBus access errors on Ubuntu.

**Purpose**: Resolves the error `[org.freedesktop.DBus.Error.AccessDenied] An AppArmor policy prevents this sender from sending this message`

**Installation**:
```bash
sudo mkdir -p /etc/apparmor.d/local
sudo cp apparmor-bluetooth-fix /etc/apparmor.d/local/usr.lib.bluetooth.bluetoothd
sudo apparmor_parser -r /etc/apparmor.d/usr.lib.bluetooth.bluetoothd
sudo systemctl restart bluetooth
```

See [TROUBLESHOOTING.md](../TROUBLESHOOTING.md) for detailed instructions.

### `home-assistant-bluetooth-example.yaml`

Example Home Assistant configuration for Bluetooth integration.

**Usage**: 
- Review this file for examples of how to configure Bluetooth in Home Assistant
- Copy relevant sections to your Home Assistant `configuration.yaml` file
- Restart Home Assistant after making changes

## Support

For detailed troubleshooting steps and alternative solutions, see [TROUBLESHOOTING.md](../TROUBLESHOOTING.md).
