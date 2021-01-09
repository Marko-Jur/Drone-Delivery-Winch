#include "Pin_Assignments.h"
#include "Winch_Libraries.h"
#include "feedback.h"

Encoder wire_drum (CLKPIN_DRUM, DTPIN_DRUM);

double  read_time_uS = 0;
long    current_pos, prev_pos;

void resetEncoder(struct encoder_data * enc_data){
   wire_drum.write(0);
   enc_data->position_m = 0;
   current_pos = wire_drum.read();
   prev_pos = wire_drum.read();
   read_time_uS = micros();
}

void readEncoder(struct encoder_data * feedback_data){
   double current_time_uS = micros();
   double time_step_uS = (current_time_uS - read_time_uS);
   current_pos = wire_drum.read();
   feedback_data->state = current_pos;
   feedback_data->speed_rps = ((current_pos - prev_pos)*1000000.0/((feedback_data->states_per_turn)*time_step_uS));
   feedback_data->speed_mps = (feedback_data->speed_rps) * 2 * PI * (feedback_data->drum_radius_m);
   feedback_data->position_m = (feedback_data->position_m) + (feedback_data->speed_mps)*time_step_uS*0.000001;

   prev_pos = current_pos;
   
}
