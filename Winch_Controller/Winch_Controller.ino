#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"
#include "PID.h"

int32_t l_bound = 0;
int32_t u_bound = 20;
int32_t i_l_bound = -10;
int32_t i_u_bound = 10;

struct control_array speed_PID_vals;
struct encoder_data enc_drum;

Servo brake_servo;
PID speed_controller = PID(l_bound, u_bound, i_l_bound, i_u_bound, true);

void setup() {
  Serial.begin(115200);
  speed_controller.setConstants(1.0, 0.0, 0.0);
  speed_controller.begin(1000, 15000, 5, &speed_PID_vals);
  
  enc_drum.drum_radius_m = 7.5*0.001;
  enc_drum.states_per_turn = 80;

  encoderSetup(&enc_drum);
  brake_servo.attach(BRAKE_SERVO_PIN);

}

void loop() {
  
  calcEncData(&enc_drum);
  speed_PID_vals.target_val = 1.5;
  speed_PID_vals.current_val = enc_drum.speed_mps;
  Serial.print("speed (m/s): ");
  Serial.println(enc_drum.speed_mps, 6);
  Serial.print("pos (m): ");
  Serial.println(enc_drum.position_m, 6);
  Serial.print("Actuator out :");
  Serial.println(speed_PID_vals.return_val*1000/u_bound + 1000);
  brake_servo.writeMicroseconds(speed_PID_vals.return_val*1000/u_bound + 1000);
  delay(50);
  
}
