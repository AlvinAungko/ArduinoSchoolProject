#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>
#include <SoftwareSerial.h>


SoftwareSerial nodemcu(8, 9);
String sdata;
char auth[] = "kvBuZuwcA_JGDj0DBMBlgXfqfe9-B_Lr";

const char *ssid = "GUSTO_289";
const char password = "Gusto@123";

int pinRedLed = 12;
int pinGreenLed = 11;
int pinSensor = A5;
int THRESHOLD = 250;
int buzzer = 10;
int rdata = 0;

char redData;

String mystring;
String sdata;

BlynkTimer timer;

void myTimerEvent() {
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
}

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(pinRedLed, OUTPUT);
  pinMode(pinGreenLed, OUTPUT);
  pinMode(pinSensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sensorvalue1);
}

void sensorvalue1() {
  sdata = myString;
  Blynk.virtualWrite(V12, sdata);
  myString = "";
}


void loop() {


  int rdata = analogRead(pinSensor);
  Serial.print("Methane Range: ");
  Serial.println(rdata);

  if (Serial.available() == 0) {
    Blynk.run();
    timer.run();  // Initiates BlynkTimer
  }

  if (Serial.available() > 0) {
    redData = Serial.read();
    myString = myString + redData;
  }


  if (rdata >= THRESHOLD) {
    digitalWrite(pinRedLed, HIGH);
    digitalWrite(pinGreenLed, LOW);
    digitalWrite(buzzer, HIGH);

    delay(50);

  } else {
    digitalWrite(pinRedLed, LOW);
    digitalWrite(pinGreenLed, HIGH);
    digitalWrite(buzzer, LOW);
  }

  if (nodemcu.available() > 0) {
    char data;
    data = nodemcu.read();
    Serial.println(data);
  }
  if (rdata < 250) {
    mystring = mystring + "Methane Range: " + rdata;
    nodemcu.println(mystring);
    Serial.println(mystring);

  } else {
    mystring = "Food Spoiled";
    nodemcu.println(mystring);
    Serial.println(mystring);
  }

  mystring = "";
  delay(1000);
}
