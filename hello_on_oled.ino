#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED I2C address
#define OLED_ADDR 0x3C

// Create OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C (ESP32)
  Wire.begin(21, 22);   // SDA, SCL

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("❌ OLED not detected");
    while (1);
  }

  // Clear display
  display.clearDisplay();

  // Set smaller text size
  display.setTextSize(1.5);          // 🔹 Small text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 2);         // Top-left corner

  // Print text
  display.println("Hello World");

  // Show on display
  display.display();
}

void loop() {
  // Nothing here
}
