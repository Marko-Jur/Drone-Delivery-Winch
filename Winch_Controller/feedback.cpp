#include "Pin_Assignments.h"
#include "Winch_Libraries.h"
#include "feedback.h"

Encoder wire_drum (CLKPIN_DRUM, DTPIN_DRUM);

double  read_time_uS = 0;
long    current_pos, prev_pos;

void resetEncoder(){
   wire_drum.write(0);
   current_pos = wire_drum.read();
   prev_pos = wire_drum.read();
   read_time_uS = micros();
}

void readEncoder(struct encoder_data * feedback_data){
   double current_time_uS = micros();
   double time_step_uS = (current_time_uS - read_time_uS);
   current_pos = wire_drum.read();

   feedback_data->enc_speed_rps = ((current_pos - prev_pos)*1000000/((feedback_data->states_per_turn)*time_step_uS));
   feedback_data->enc_speed_mps = (feedback_data->enc_speed_rps) * 2 * PI * (feedback_data->drum_radius_m);
   feedback_data->enc_position_m += (feedback_data->enc_speed_mps)*time_step_uS/1000000;

   prev_pos = current_pos;
   
}
