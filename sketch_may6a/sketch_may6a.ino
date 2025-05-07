#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID ""    //WIFI SSID name
#define WIFI_PASS ""    // WIFI password

#define FIREBASE_HOST ""    // FIrebase Hosting adress
#define FIREBASE_AUTH ""    // Firebase authentication

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

  if (Firebase.setInt(firebaseData, "/value", rssi)) // Firebase path
  {
    Serial.println("RSSI Updated: " + String(rssi));
  } else {
    Serial.println("Firebase Error: " + firebaseData.errorReason());
  }

  delay(1000); 
}
