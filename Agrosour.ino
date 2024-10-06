#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <SoftwareSerial.h>
const byte nitro[] = { 0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c };
const byte phos[] = { 0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc };
const byte pota[] = { 0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0 };

const int moisturePin = A0;
const int dhtPin = 4;

#define DHTTYPE DHT22  
DHT dht(dhtPin, DHTTYPE);

// Firebase configuration
#define FIREBASE_HOST "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "your-api-key"

// Wi-Fi credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
FirebaseData firebaseData;
byte values[8];
SoftwareSerial npkSerial(17, 16);  // GPIO 17 TX, GPIO 16 RX

void setup() {
  // Initialize Serial communication
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

  //TTL communication for NPK sensor
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

  //moisture value
  moistureValue = analogRead(moisturePin);

  //DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  //JSON structure for sensor data
  String jsonData = "{\"sensor_data\": {\"sensor_id\": {\"humidity\": " + String(humidity / 100.0) +
                    ", \"moisture\": " + String(moistureValue / 1023.0) +
                    ", \"nitrogen\": " + String(val1) +
                    ", \"phosphorus\": " + String(val2) +
                    ", \"potassium\": " + String(val3) +
                    ", \"temperature\": " + String(temperature) + "}}}";

  //Firebase
  if (Firebase.ready()) {
    if (Firebase.setString(firebaseData, "/sensor_data", jsonData)) {
      Serial.println("Data sent to Firebase!");
    } else {
      Serial.println("Failed to send data: " + firebaseData.errorReason());
    }
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
