#!/bin/bash
# Setup script to fix Home Assistant Bluetooth/DBus AppArmor issues
# Run this script with sudo privileges

set -e

echo "=========================================="
echo "Home Assistant Bluetooth/DBus Fix Script"
echo "=========================================="
echo ""

# Check if running as root
if [ "$EUID" -ne 0 ]; then 
   echo "ERROR: This script must be run as root (use sudo)"
   exit 1
fi

echo "Step 1: Backing up existing AppArmor configuration..."
if [ -d "/etc/apparmor.d" ]; then
    BACKUP_DIR="/etc/apparmor.d/backup-$(date +%Y%m%d-%H%M%S)"
    mkdir -p "$BACKUP_DIR"
    if [ -f "/etc/apparmor.d/usr.bin.homeassistant" ]; then
        cp /etc/apparmor.d/usr.bin.homeassistant "$BACKUP_DIR/" || true
        echo "  ✓ Backed up existing profile to $BACKUP_DIR"
    fi
fi

echo ""
echo "Step 2: Installing AppArmor profile for Home Assistant..."
cp apparmor.d/usr.bin.homeassistant /etc/apparmor.d/
chmod 644 /etc/apparmor.d/usr.bin.homeassistant
echo "  ✓ AppArmor profile installed"

echo ""
echo "Step 3: Reloading AppArmor profiles..."
if command -v apparmor_parser &> /dev/null; then
    apparmor_parser -r /etc/apparmor.d/usr.bin.homeassistant
    echo "  ✓ AppArmor profile reloaded"
else
    echo "  ⚠ apparmor_parser not found, will reload via systemctl"
    systemctl reload apparmor || systemctl restart apparmor
fi

echo ""
echo "Step 4: Checking Bluetooth service status..."
systemctl status bluetooth --no-pager -l || true

echo ""
echo "Step 5: Restarting Bluetooth service..."
systemctl restart bluetooth
echo "  ✓ Bluetooth service restarted"

echo ""
echo "Step 6: Verifying Bluetooth controller..."
hciconfig hci0 up || echo "  ⚠ Could not bring up hci0 (may need manual intervention)"
hciconfig || echo "  ⚠ hciconfig not available"

echo ""
echo "=========================================="
echo "Setup complete!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "1. Restart Home Assistant: sudo systemctl restart home-assistant@homeassistant"
echo "2. Check Home Assistant logs: journalctl -u home-assistant@homeassistant -f"
echo "3. If issues persist, check AppArmor logs: sudo dmesg | grep -i apparmor"
echo ""
echo "Alternative: If you want to temporarily disable AppArmor for troubleshooting:"
echo "  sudo aa-complain /etc/apparmor.d/usr.bin.homeassistant"
echo ""
