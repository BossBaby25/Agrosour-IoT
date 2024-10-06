#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// NPK Sensor Requests (TTL Communication)
const byte nitro[] = { 0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c };
const byte phos[] = { 0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc };
const byte pota[] = { 0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0 };

const int moisturePin = A0;  // soil moisture sensor
const int dhtPin = 4;       //DHT22 sensor

#define DHTTYPE DHT22
DHT dht(dhtPin, DHTTYPE);

// Firebase configuration
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

// Wi-Fi credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Declare Firebase Data object
FirebaseData firebaseData;

// A variable to store NPK values
byte values[8];

// SoftwareSerial for TTL communication (TX, RX)
SoftwareSerial npkSerial(17, 16);  // GPIO 17 TX, GPIO 16 RX

void setup() {
  Serial.begin(9600);

  // Initialize Wi-Fi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  npkSerial.begin(9600);
  dht.begin();
}

void loop() {
  byte val1 = nitrogen();
  delay(250);
  byte val2 = phosphorous();
  delay(250);
  byte val3 = potassium();
  delay(250);

  int moistureValue = analogRead(moisturePin);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (Firebase.ready()) {
    Firebase.setInt(firebaseData, "/NPK/Nitrogen", val1);
    Firebase.setInt(firebaseData, "/NPK/Phosphorous", val2);
    Firebase.setInt(firebaseData, "/NPK/Potassium", val3);
    Firebase.setInt(firebaseData, "/Moisture", moistureValue);
    Firebase.setFloat(firebaseData, "/Temperature", temperature);
    Firebase.setFloat(firebaseData, "/Humidity", humidity);
    
    Serial.println("Data sent to Firebase!");
  } else {
    Serial.println("Firebase connection failed.");
  }

  delay(5000);
}

byte nitrogen() {
  npkSerial.write(nitro, 8);
  delay(100);
  for (byte i = 0; i < 8; i++) {
    values[i] = npkSerial.read();
  }
  return values[4];
}

byte phosphorous() {
  npkSerial.write(phos, 8);
  delay(100);
  for (byte i = 0; i < 8; i++) {
    values[i] = npkSerial.read();
  }
  return values[4];
}

byte potassium() {
  npkSerial.write(pota, 8);
  delay(100);
  for (byte i = 0; i < 8; i++) {
    values[i] = npkSerial.read();
  }
  return values[4];
}
