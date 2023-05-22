#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>

String sdata;

char auth[] = "kvBuZuwcA_JGDj0DBMBlgXfqfe9-B_Lr";

const char *ssid = "GUSTO_289";
const char password = "Gusto@123";

char redData;
String sdata;
BlynkTimer timer;

void setup() {
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sensorvalue1);
}

void loop() {
  if (Serial.available() == 0) {
    Blynk.run();
    timer.run();  // Initiates BlynkTimer
  }

  if (Serial.available() > 0) {
    redData = Serial.read();
    myString = myString + redData;
  }
}