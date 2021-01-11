#ifndef _FEEDBACK_H
#define _FEEDBACK_H

//structures

typedef struct encoder_data{
  //data in
  float drum_radius_m;
  uint16_t states_per_turn;
  
  //data out
  float speed_mps;
  float speed_rps;
  float position_m = 0;
  long  state = 0;
}encoder_data;

//function declarations

void resetEncoder(struct encoder_data * feedback_data);
void readEncoder(struct encoder_data * feedback_data);

  
#endif
