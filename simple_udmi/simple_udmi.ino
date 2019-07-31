// Tested with an Uno

#include <ArduinoJson.h>
int count = 0;
int x = 2000;
int y = 500;
int bub = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

// Might be good to use an interrupt for the 'light switch'

void loop() {


  int bib = digitalRead(2);
  if (bib == HIGH && bub == LOW) {
      digitalWrite(3, !digitalRead(3));
  }
  
  int bob = analogRead(0);
  analogWrite(5, 255-bob);

  bub = bib;
  
  StaticJsonDocument<200> udmi_out;
  
  //  build udmi

  udmi_out["version"] = 1;
  udmi_out["timestamp"] = "0";
  udmi_out["points"]["lux_level"]["present_value"] = bob;
  udmi_out["points"]["lum_value"]["present_value"] = digitalRead(3)*100;
  udmi_out["points"]["dimmer_value"]["present_value"] = 255-bob;

  //  write udmi
  
  serializeJson(udmi_out, Serial);
  Serial.println();
  
}
