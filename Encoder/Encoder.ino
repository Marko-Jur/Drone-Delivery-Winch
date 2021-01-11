#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"

struct encoder_data wire_drum;

void setup() {
  encoderSetup(&wire_drum);
  wire_drum.drum_radius_m = 7.5*0.001;
  wire_drum.states_per_turn = 4096;
}

void loop(){
  calcEncData(&wire_drum);
  delay(50);
}
