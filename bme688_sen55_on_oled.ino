#include <Arduino.h>
#include <Wire.h>

/* SEN55 */
#include <SensirionI2CSen5x.h>

/* BME688 */
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

/* OLED */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* OLED settings */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
#define OLED_ADDR    0x3C

#define LINE_HEIGHT   14
#define HEADER_HEIGHT 16

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SensirionI2CSen5x sen5x;
Adafruit_BME680 bme;   // BME688 (I2C)

void setup() {
    Serial.begin(115200);
    delay(1000);

    /* I2C */
    Wire.begin(21, 22);

    /* OLED init */
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        while (1);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setRotation(1);   // Portrait mode

    /* SEN55 init */
    sen5x.begin(Wire);
    sen5x.deviceReset();
    sen5x.startMeasurement();

    /* BME688 init */
    if (!bme.begin(0x76)) {
        display.setCursor(0, 0);
        display.println("BME688 ERROR");
        display.display();
        while (1);
    }

    // BME688 config (Temp + RH only)
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_NONE);
    bme.setGasHeater(0, 0);

    Serial.println("SEN55 + BME688 + OLED READY");
}

void loop() {
    /* -------- Read SEN55 -------- */
    float pm1, pm2_5, pm4, pm10;
    float sen_rh, sen_temp;   // ignored
    float voc, nox;

    if (sen5x.readMeasuredValues(pm1, pm2_5, pm4, pm10,
                                 sen_rh, sen_temp, voc, nox)) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("SEN55 ERROR");
        display.display();
        delay(2000);
        return;
    }

    /* -------- Read BME688 -------- */
    if (!bme.performReading()) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("BME688 ERROR");
        display.display();
        delay(2000);
        return;
    }

    float temperature = bme.temperature;
    float humidity    = bme.humidity;

    /* -------- OLED Display -------- */
    display.clearDisplay();

    /* Header */
    display.setCursor(0, 0);
    display.println("DEVICE 1");
    display.drawLine(0, 10, 63, 10, SSD1306_WHITE);

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
    display.print("Temp  "); display.println(temperature, 1);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("RH    "); display.println(humidity, 0);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("VOC   ");
    isnan(voc) ? display.println("n/a") : display.println(voc, 0);
    y += LINE_HEIGHT;

    display.setCursor(0, y);
    display.print("NOx   ");
    isnan(nox) ? display.println("n/a") : display.println(nox, 1);

    display.display();
    delay(2000);
}

