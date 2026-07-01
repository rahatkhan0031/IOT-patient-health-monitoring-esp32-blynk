// IoT Based Patient Health Monitoring System using ESP32 and Blynk

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Patient Health Monitoring"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>

#include "MAX30100_PulseOximeter.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#include "DHT.h"

// ---------------- Pin Definitions ----------------
#define DHTPIN 18
#define DHTTYPE DHT11
#define DS18B20_PIN 5

// ESP32 default I2C pins:
// SDA = GPIO 21
// SCL = GPIO 22

// ---------------- WiFi Details ----------------
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ---------------- Objects ----------------
PulseOximeter pox;
BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// ---------------- Variables ----------------
float roomTemperature;
float roomHumidity;
float bodyTemperature;
float BPM;
float SpO2;

// ---------------- Beat Callback ----------------
void onBeatDetected() {
  Serial.println("Beat Detected!");
}

// ---------------- Send Sensor Data ----------------
void sendSensorData() {
  roomTemperature = dht.readTemperature();
  roomHumidity = dht.readHumidity();

  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();

  sensors.requestTemperatures();
  bodyTemperature = sensors.getTempCByIndex(0);

  Serial.println("------------ Patient Health Data ------------");

  // DHT11 check
  if (isnan(roomTemperature) || isnan(roomHumidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.print("Room Temperature: ");
    Serial.print(roomTemperature);
    Serial.println(" °C");

    Serial.print("Room Humidity: ");
    Serial.print(roomHumidity);
    Serial.println(" %");

    Blynk.virtualWrite(V3, roomTemperature);
    Blynk.virtualWrite(V4, roomHumidity);
  }

  // MAX30100 values
  Serial.print("Heart Rate: ");
  Serial.print(BPM);
  Serial.println(" bpm");

  Serial.print("SpO2: ");
  Serial.print(SpO2);
  Serial.println(" %");

  Blynk.virtualWrite(V5, BPM);
  Blynk.virtualWrite(V6, SpO2);

  // DS18B20 check
  if (bodyTemperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Failed to read from DS18B20 sensor!");
  } else {
    Serial.print("Body Temperature: ");
    Serial.print(bodyTemperature);
    Serial.println(" °C");

    Blynk.virtualWrite(V7, bodyTemperature);
  }

  Serial.println("---------------------------------------------");
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  pinMode(DHTPIN, INPUT);

  dht.begin();
  sensors.begin();

  Wire.begin(21, 22);   // SDA, SCL for ESP32

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.print("Initializing MAX30100 Pulse Oximeter... ");

  if (!pox.begin()) {
    Serial.println("FAILED");
    while (1);
  } else {
    Serial.println("SUCCESS");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  timer.setInterval(1000L, sendSensorData);
}

// ---------------- Loop ----------------
void loop() {
  pox.update();   // Must run very frequently
  Blynk.run();
  timer.run();
}