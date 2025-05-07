#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "ELETH"
#define WIFI_PASS "eleth333"

#define FIREBASE_HOST "https://esp-location-ac913-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "AIzaSyAfqbfOrEsei1lT9Wu022ASsqDHpRI4TAg"

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi CONNECTED");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  int rssi = WiFi.RSSI();

  if (Firebase.setInt(firebaseData, "/value", rssi)) {
    Serial.println("RSSI Updated: " + String(rssi));
  } else {
    Serial.println("Firebase Error: " + firebaseData.errorReason());
  }

  delay(1000); 
}
