// Tested with an Uno

#include <ArduinoJson.h>
int count = 0;
int x = 2000;
int y = 500;
int bub = 0;
int incoming_byte = 0;
boolean remote_override = false;
StaticJsonDocument<200> udmi_out;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

// TODO: Might be good to use an interrupt for the 'light switch'

void loop() {

  // Monitor inputs

  int bib = digitalRead(2);

  if (bib == HIGH) {
    remote_override = false; 
  }
  
  if (bib == HIGH && bub == LOW && remote_override == false) {
      digitalWrite(3, !digitalRead(3));
  }
  
  int bob = analogRead(0);
  analogWrite(5, 255-bob);

  bub = bib;

  if (Serial.available() > 0) {
    remote_override = true;
    // read the incoming byte:
    incoming_byte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incoming_byte, DEC);
    digitalWrite(3, !digitalRead(3));
  }

  // Generate output
  
  
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
