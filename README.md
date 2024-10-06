# Smart Agriculture System with ESP32

## Overview

This project implements a **Smart Agriculture System** using the ESP32 microcontroller, integrating several sensors: **DHT22** for temperature and humidity, a **soil moisture sensor**, and an **NPK soil sensor**. The collected sensor data is sent to Firebase in a structured JSON format, which can be visualized through a mobile app or web platform for real-time monitoring and decision-making.

### Features:
- **Temperature and Humidity Monitoring** using DHT22
- **Soil Moisture Level Detection** using a soil moisture sensor
- **NPK Sensor Readings** via RS485-to-TTL for Nitrogen, Phosphorus, and Potassium levels
- **Real-time Firebase Integration**

## Hardware Components

- **ESP32 Microcontroller**
- **DHT22 Sensor** (for temperature and humidity)
- **NPK Soil Sensor** (for nitrogen, phosphorus, and potassium values)
- **Soil Moisture Sensor**
- **RS485-to-TTL Converter** (for connecting the NPK sensor)
- **Power Supply (12V for the NPK sensor)**

## Schematic Diagram

Refer to the provided schematic for wiring details. The RS485-to-TTL converter connects the NPK sensor to the ESP32's RX and TX pins, and the soil moisture sensor connects to an analog pin.

## Pin Configuration

| Component           | ESP32 Pin |
|---------------------|-----------|
| **DHT22 Data Pin**   | GPIO 4    |
| **Soil Moisture Pin**| A0        |
| **RS485 TX**         | GPIO 17   |
| **RS485 RX**         | GPIO 16   |

## JSON Data Structure

The sensor data is sent to Firebase in the following JSON format:

```json
{
  "sensor_data": {
    "sensor_id": {
      "humidity": 0.6,
      "moisture": 0.8,
      "nitrogen": 110,
      "phosphorus": 130,
      "potassium": 110,
      "temperature": 30
    }
  }
}
