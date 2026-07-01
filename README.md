<img width="2880" height="1440" alt="circuit-diagram" src="https://github.com/user-attachments/assets/7865b63a-52fb-4d58-8155-f929e7956385" /><img width="2880" height="1440" alt="circuit-diagram" src="https://github.com/user-attachments/assets/c8ae3ddc-8e53-44c5-a957-8141b3589955" /># IoT Patient Health Monitoring System using ESP32 and Blynk

This project is an IoT-based patient health monitoring system using an ESP32 microcontroller and the Blynk IoT platform. The system measures heart rate, blood oxygen level, room temperature, room humidity, and body temperature using multiple sensors. The measured data is displayed on the Blynk mobile app and also printed on the Arduino Serial Monitor.

## Project Overview

The system is designed as a simple health monitoring prototype. It collects sensor data from the patient and the surrounding environment, then sends the data wirelessly to the Blynk app using WiFi.

This project is useful for learning embedded systems, IoT communication, sensor interfacing, and real-time health data monitoring.

## Features

- Measures heart rate in BPM
- Measures blood oxygen saturation level, SpO2
- Measures room temperature
- Measures room humidity
- Measures body temperature
- Sends sensor data to the Blynk IoT app
- Displays live values on the Serial Monitor
- Uses ESP32 WiFi connectivity

## Components Used

| Component | Purpose |
|---|---|
| ESP32 Development Board | Main microcontroller with WiFi |
| MAX30100 Sensor | Heart rate and SpO2 measurement |
| DHT11 Sensor | Room temperature and humidity measurement |
| DS18B20 Sensor | Body temperature measurement |
| 4.7kΩ Resistor | Pull-up resistor for DS18B20 data line |
| Jumper Wires | Circuit connections |
| Breadboard | Prototyping |
| Blynk App | IoT dashboard and data display |

## Circuit Diagram

The circuit connection for the IoT patient health monitoring system is shown below:

![Circuit Diagram](circuit-diagram.png)

## Pin Connection

| Sensor / Module | Pin | ESP32 Pin |
|---|---|---|
| MAX30100 | SDA | GPIO 21 |
| MAX30100 | SCL | GPIO 22 |
| MAX30100 | VIN | 3.3V |
| MAX30100 | GND | GND |
| DHT11 | Data | GPIO 18 |
| DHT11 | VCC | 3.3V |
| DHT11 | GND | GND |
| DS18B20 | Data | GPIO 5 |
| DS18B20 | VCC | 3.3V |
| DS18B20 | GND | GND |

Note: Connect a 4.7kΩ resistor between the DS18B20 data pin and 3.3V.

## Blynk Virtual Pins

| Sensor Data | Blynk Virtual Pin |
|---|---|
| Room Temperature | V3 |
| Room Humidity | V4 |
| Heart Rate | V5 |
| SpO2 | V6 |
| Body Temperature | V7 |

## Required Libraries

Install the following libraries in the Arduino IDE:

- Blynk
- WiFi
- MAX30100 PulseOximeter
- DHT sensor library
- OneWire
- DallasTemperature

## How the System Works

1. The ESP32 connects to a WiFi network.
2. The MAX30100 sensor measures heart rate and SpO2.
3. The DHT11 sensor measures room temperature and humidity.
4. The DS18B20 sensor measures body temperature.
5. The ESP32 sends the collected data to the Blynk app.
6. The values are displayed in real time on the mobile dashboard.

## Code Configuration

Before uploading the code to the ESP32, update the following details in the Arduino sketch:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
