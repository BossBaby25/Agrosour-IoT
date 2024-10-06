# **Agrosour-IoT**


This project implements a smart agriculture system using an ESP32 microcontroller. The system gathers real-time data from:
- **NPK Soil Sensor** (Nitrogen, Phosphorus, Potassium levels) via **RS485-to-TTL communication**.
- **DHT22 Sensor** (Temperature and Humidity).
- **Soil Moisture Sensor**.

The collected data is transmitted to **Firebase** for monitoring and analysis, allowing farmers to track soil health, temperature, and humidity in real-time.

## **Table of Contents**
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation and Setup](#installation-and-setup)
- [Code Explanation](#code-explanation)
- [Usage](#usage)

---

## **Features**
- Real-time monitoring of NPK (Nitrogen, Phosphorus, Potassium) values using RS485-to-TTL communication.
- Measures environmental temperature and humidity using the DHT22 sensor.
- Monitors soil moisture levels using an analog moisture sensor.
- Transmits data to Firebase for storage and analysis.
- Provides insights into soil health for better agricultural decision-making.

---

## **Hardware Requirements**
- **ESP32** (with Wi-Fi capability)
- **NPK Soil Sensor** (via RS485-to-TTL module)
- **RS485-to-TTL Converter**
- **DHT22 Sensor**
- **Soil Moisture Sensor**
- **Jumper wires**
- **Breadboard**
- **12V power supply** (for NPK sensor and RS485 module)
- **5V power supply** (for ESP32)

### **Pin Connections:**

1. **NPK Sensor**:
   - **A+ Pin (RS485)** → Connect to A+ terminal of the RS485-to-TTL converter.
   - **B- Pin (RS485)** → Connect to B- terminal of the RS485-to-TTL converter.
   - **Power** → 12V power supply.
   
2. **RS485-to-TTL Converter** (Connected to ESP32):
   - **TX Pin (ESP32 GPIO 17)** → RX Pin on the TTL side of the RS485-to-TTL converter.
   - **RX Pin (ESP32 GPIO 16)** → TX Pin on the TTL side of the RS485-to-TTL converter.
   - **GND** → Common ground between ESP32 and RS485-to-TTL module.
   - **VCC** → 3.3V or 5V (depending on your RS485-to-TTL module requirement).

3. **DHT22 Sensor**:
   - **Data Pin** → ESP32 GPIO 4.
   - **Power** → 3.3V (or 5V if required by DHT22).
   - **Ground** → GND.

4. **Soil Moisture Sensor**:
   - **Analog Output Pin** → ESP32 A0.
   - **Power** → 3.3V.
   - **Ground** → GND.

---

## **Software Requirements**
- **Arduino IDE** with the ESP32 board installed.
- **FirebaseESP32** library for Firebase communication.
- **DHT Sensor** library for reading temperature and humidity.
- **Wi-Fi credentials** for ESP32.
- Firebase credentials: API key and project URL.

### **Arduino Libraries:**
You can install the following libraries via the Arduino Library Manager:
1. **FirebaseESP32** (`FirebaseESP32 by Mobizt`).
2. **DHT** (`DHT sensor library by Adafruit`).
3. **SoftwareSerial** (for serial communication).

---

## **Installation and Setup**

1. **Install Arduino IDE**: Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
   
2. **Install ESP32 Board**:
   - Open Arduino IDE.
   - Go to **File > Preferences**.
   - In the "Additional Boards Manager URLs" field, add:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to **Tools > Board > Boards Manager**. Search for **ESP32** and install the package.

3. **Install Required Libraries**:
   - Open Arduino IDE and go to **Tools > Manage Libraries**.
   - Search and install the following libraries: `FirebaseESP32`, `DHT`, `SoftwareSerial`.

4. **Firebase Setup**:
   - Create a Firebase project in the [Firebase Console](https://console.firebase.google.com/).
   - Go to **Database > Realtime Database** and create a database.
   - Get your **API Key** and **Database URL** from the Firebase Console.
   
5. **Wi-Fi Setup**: 
   - In the code, place `"your-ssid"` and `"your-password"` with your Wi-Fi credentials.
   
6. **Firebase Credentials**: 
   - Place `"your-project-id"` and `"your-api-key"` with your Firebase project details.

7. **Upload the Code**:
   - Open the Arduino IDE, copy the provided code, and upload it to the ESP32.

---

## **Code Explanation**

The project gathers data from the following sensors:
1. **NPK Sensor** (via RS485-to-TTL Serial Communication):
   - Requests Nitrogen, Phosphorous, and Potassium levels.
   - Uses `SoftwareSerial` to communicate with the NPK sensor.
   
2. **DHT22 Sensor**:
   - Measures temperature and humidity.
   
3. **Soil Moisture Sensor**:
   - Measures soil moisture using an analog pin (A0).

The data is then sent to **Firebase Realtime Database** for monitoring and analysis.

---

## **Usage**

1. **Monitor Sensor Readings**: 
   - Once the code is running on your ESP32, it will periodically read data from the sensors.
   - The data (NPK values, soil moisture, temperature, and humidity) will be sent to Firebase.

2. **Access Firebase Data**:
   - Visit your Firebase Realtime Database console to view the real-time data updates for each sensor:
     - `/NPK/Nitrogen`
     - `/NPK/Phosphorous`
     - `/NPK/Potassium`
     - `/Moisture`
     - `/Temperature`
     - `/Humidity`

---

## **Troubleshooting**

- **Wi-Fi Connection Issues**: Ensure the Wi-Fi credentials are correct and the ESP32 is within range of the Wi-Fi router.
- **Sensor Readings**: Verify that the sensors are connected correctly and powered properly.
- **Firebase Issues**: Ensure that the Firebase project and database URL are set up correctly and that the API key is valid.

