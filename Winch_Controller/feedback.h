#ifndef _FEEDBACK_H
#define _FEEDBACK_H

//structures

typedef struct encoder_data{
  //data in
  float drum_radius_m;
  uint16_t states_per_turn;
  
  //data out
  float enc_speed_mps;
  float enc_speed_rps;
  float enc_position_m = 0;
  long  enc_state = 0;
}encoder_data;

//function declarations

void resetEncoder();
void readEncoder(struct encoder_data * feedback_data);

  
#endif
