
#include <SoftwareSerial.h>


SoftwareSerial nodemcu(8, 9);
int pinRedLed = 12;
int pinGreenLed = 11;
int pinSensor = A5;
int THRESHOLD = 250;
int buzzer = 10;
int detectedValueFromSensor = 0;
String mystring;


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
}

void sensorvalue1() {
  sdata = myString;
  Blynk.virtualWrite(V12, sdata);
  myString = "";
}


void loop() {
  int detectedValueFromSensor = analogRead(pinSensor);  // Data Read By The Sensor
  Serial.print("Methane Range: ");
  Serial.println(detectedValueFromSensor);

  // If the value detected from the sensor increases above 250, this code will trigger
  if (detectedValueFromSensor >= THRESHOLD) {
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
  if (detectedValueFromSensor < 250) {
    mystring = mystring + "Methane Range: " + detectedValueFromSensor;
    nodemcu.println(mystring);
    Serial.println(mystring);

  } else {
    mystring = "Food is Spoiled";
    nodemcu.println(mystring);
    Serial.println(mystring);
  }

  mystring = "";
  delay(1000);
}
