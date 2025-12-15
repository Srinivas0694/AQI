# ESP32 Air Quality Monitoring System

## 🔌 Pin Connections (I2C)

| Device | SDA | SCL | Power |
|------|-----|-----|-------|
| ESP32 | GPIO 21 | GPIO 22 | 3.3V |
| SEN55 | GPIO 21 | GPIO 22 | 5V / 3.3V |
| BME688 | GPIO 21 | GPIO 22 | 3.3V |
| OLED (SSD1306) | GPIO 21 | GPIO 22 | 3.3V |

> All devices share the same I2C bus.

---

## 🖥️ Output Display (OLED – Portrait Mode)

DEVICE 1
────────
PM1.0   3.9
PM2.5   4.3
PM4.0   4.4
PM10    4.4
Temp    23.0°C
RH      46 %
VOC     105
NOx     1.0

![WhatsApp Image 2025-12-15 at 15 47 11_64a4179c](https://github.com/user-attachments/assets/d11b9136-87af-413d-8794-d3707719054b)

