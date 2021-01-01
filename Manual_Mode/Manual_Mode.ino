#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Manual_Mode.h"

int transmitter_values[8] = {0,0,0,0,0,0,0,0}; // Right Lateral, Right up/down, Thottle, Left lateral, switch A, switch B, Switch C, Switch D

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  rcSetup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  rcReader(transmitter_values);
  manualMotorController(transmitter_values);
}
