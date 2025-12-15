#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Create BME688 object (I2C)
Adafruit_BME680 bme;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 + BME688 Temperature & Humidity (0x76)");

  // Initialize I2C for ESP32
  Wire.begin(21, 22);   // SDA, SCL

  // Initialize BME688 with I2C address 0x76
  if (!bme.begin(0x76)) {
    Serial.println("❌ BME688 not found at 0x76");
    while (1);
  }

  Serial.println("✅ BME688 detected");

  // Configure only required oversampling
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);

  // Disable unused sensors (optional but recommended)
  bme.setPressureOversampling(BME680_OS_NONE);
  bme.setGasHeater(0, 0);   // Disable gas heater
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("❌ Failed to perform reading");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(bme.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.println("--------------------");
  delay(2000);
}



