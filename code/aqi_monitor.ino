#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "BluetoothSerial.h"
#include <WiFi.h>
#include "ThingSpeak.h"



// ---------- Pin setup ----------
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ135_PIN 36

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
const char* ssid = "YOUR_WIFI_NAME"; //replace wifi name
const char* password = "YOUR_WIFI_PASSWORD"; //replace with wifi password

unsigned long channelID = 0000000; //repalce with channel id
const char* writeAPIKey = "XXXXXXXXXXXX"; //replace with write api key


WiFiClient client;


// ---------- Objects ----------
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool oledAvailable = false;

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
Serial.print("Connecting to WiFi");

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

Serial.println("\nWiFi Connected");

ThingSpeak.begin(client);

  delay(1000);
  Serial.println("ESP32 Starting...");
  SerialBT.begin("ESP32_AIR_MONITOR");
  Serial.println("Bluetooth Started");
  analogSetPinAttenuation(MQ135_PIN, ADC_11db);

  


  // Init DHT
  dht.begin();

  // Init OLED (DO NOT FREEZE if not found)
  if (display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    oledAvailable = true;
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(20, 25);
    display.print("Sensor System");
    display.display();
    delay(2000);
  } else {
    Serial.println("OLED not found, continuing without display.");
  }

  Serial.println("Setup complete.");
}

void loop() {
  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();   // FLOAT ✔
  int mq135Value = analogRead(MQ135_PIN);
  

  // Handle DHT error safely
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT Sensor Error!");
    delay(2000);
    return;
  }
  ThingSpeak.setField(1, temperature);
ThingSpeak.setField(2, humidity);
ThingSpeak.setField(3, mq135Value);

int status = ThingSpeak.writeFields(channelID, writeAPIKey);

if(status == 200){
  Serial.println("ThingSpeak upload success");
} else {
  Serial.println("Upload failed");
}

  // ---- Serial Output ----
  Serial.print("Temp: ");
  Serial.print(temperature, 1);
  Serial.print(" C | Hum: ");
  Serial.print(humidity, 1);
  Serial.print(" % | MQ135: ");
  Serial.println(mq135Value);
  // ---- Bluetooth Output ----
SerialBT.print("Temp: ");
SerialBT.print(temperature, 1);
SerialBT.print(" C | Hum: ");
SerialBT.print(humidity, 1);
SerialBT.print(" % | MQ135: ");
SerialBT.print(mq135Value);

// Alert logic (no buzzer)
if (mq135Value > 800) {
  SerialBT.println(" | STATUS: POOR ⚠");
} else {
  SerialBT.println(" | STATUS: NORMAL");
}

  // ---- OLED Output (only if present) ----
  if (oledAvailable) {
    display.clearDisplay();

    // Temperature
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("TEMPERATURE");
    display.setTextSize(2);
    display.setCursor(0, 12);
    display.print(temperature, 1);
    display.print(" C");

    // Humidity (FLOAT displayed)
    display.setTextSize(1);
    display.setCursor(0, 32);
    display.print("HUMIDITY");
    display.setTextSize(2);
    display.setCursor(0, 44);
    display.print(humidity, 1);
    display.print(" %");

    // MQ135 Gas value
    display.setTextSize(1);
    display.setCursor(80, 42);
    display.print("MQ135:");
    display.setCursor(80, 54);
    display.print(mq135Value);

    display.display();
  }

delay(15000);
}
