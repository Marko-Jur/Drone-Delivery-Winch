#ifndef _MAGENC_H
#define _MAGENC_H

//function declarations 

void encoderSetup(struct encoder_data * feedback_data);
void calcEncData(struct encoder_data * feedback_data);
unsigned int readEncSensor();

//structures

typedef struct encoder_data{
  //data in
  float drum_radius_m;
  uint16_t states_per_turn;
  
  //data out
  float speed_mps;
  float speed_rps;
  float position_m = 0;
  unsigned int prev_state = 0;
  unsigned int rotary_state = 0;
}encoder_data;


#endif 
