
#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define firebaseHost  "https://iotarduinoproj-default-rtdb.firebaseio.com/"
#define firebaseAuth  "JzhzwGZNc3zM6g2wLFT4W0LvAkPvRfrIcNeADVuu"
#define ssid  "GUSTO WIFI"
#define password  "Gusto@123"

FirebaseData fbdo;
FirebaseConfig config;
FirebaseAuth auth;
int pinSensor = A0;
int THRESHOLD = 250;
int detectedValueFromSensor = 0;
unsigned long sendDataPrevMillis = 0;
int count = 0;
String mystring;
bool signupOK = false;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  pinMode(pinSensor, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  config.api_key = firebaseAuth;
  config.database_url = firebaseHost;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}


void loop() {

  int detectedValueFromSensor = analogRead(pinSensor);  // Data Read By The Sensor
  Serial.print("Methane Range: ");
  Serial.println(detectedValueFromSensor);
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.setInt(&fbdo, "food_status", detectedValueFromSensor)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
  }

}
