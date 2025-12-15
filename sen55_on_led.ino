#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2CSen5x.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* OLED settings */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

#define LINE_HEIGHT 14     // Large spacing (no mixing)
#define HEADER_HEIGHT 16   // Space for DEVICE label

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SensirionI2CSen5x sen5x;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Wire.begin(21, 22);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        while (1);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    // Portrait orientation
    display.setRotation(1);

    sen5x.begin(Wire);
    sen5x.deviceReset();
    sen5x.startMeasurement();
}

void loop() {
    float pm1, pm2_5, pm4, pm10;
    float temp, rh, voc, nox;

    if (sen5x.readMeasuredValues(pm1, pm2_5, pm4, pm10,
                                 rh, temp, voc, nox)) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("SEN55 ERROR");
        display.display();
        delay(1000);
        return;
    }

    display.clearDisplay();

    /* ---------- HEADER ---------- */
    display.setCursor(0, 0);
    display.println("DEVICE 1");
    display.drawLine(0, 10, 63, 10, SSD1306_WHITE);

    /* ---------- DATA START ---------- */
    int y = HEADER_HEIGHT;

    display.setCursor(0, y);
    display.print("PM1.0 "); display.println(pm1, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("PM2.5 "); display.println(pm2_5, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("PM4.0 "); display.println(pm4, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("PM10  "); display.println(pm10, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("Temp  "); display.println(temp, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("RH    "); display.println(rh, 0);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("VOC   "); display.println(voc, 0);

    display.display();
    delay(1000);
}

