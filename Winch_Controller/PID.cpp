#include "Winch_Libraries.h"
#include "PID.h"

int32_t PID::_u_bound;
int32_t PID::_l_bound;  
int32_t PID::_i_u_bound;
int32_t PID::_i_l_bound;

bool PID::_bounds_valid;
bool PID::_gains_valid;

struct gain_vals PID::_gains;
struct control_array * PID::_control_vals;

float PID::_time_step_uS;
float PID::_integrator; 


PID::PID(int32_t l_bound, int32_t u_bound, int32_t integrator_l_bound, int32_t integrator_u_bound, bool anti_windup_state)  {
  _u_bound = u_bound;
  _l_bound = l_bound;
  if (anti_windup_state == true && (integrator_u_bound > integrator_l_bound)) {
    _i_u_bound = integrator_u_bound;
    _i_l_bound = integrator_l_bound;
  }
  else {
    _i_u_bound = _i_l_bound = 0;
  }

  if (_u_bound > l_bound)
    _bounds_valid = true;
  else 
    _bounds_valid = false;
}

void PID::setConstants(float kP, float kI, float kD) {
  _gains.kP = kP;
  _gains.kI = kI;
  _gains.kD = kD;
  if((_gains.kP != 0) && (_gains.kI != 0) && (_gains.kD != 0))
    _gains_valid = true;
  else 
    _gains_valid = false;
}

bool PID::begin(int32_t op_period, struct control_array * control_vals){
  if (_gains_valid == false || _bounds_valid == false || control_vals == NULL || op_period == 0){
    return false;
  }
  else{
    _control_vals = control_vals;
    _integrator = 0;
    _time_step_uS = op_period;
    mainLoop.begin(PID::controlLoop, op_period); 
    return true;
  }
}

void PID::controlLoop() {

  Serial.println("control loop FUCKING WORKS!!!! O.O");
  float error = (_control_vals->target_val) - (_control_vals->current_val);
  float pid_out;
  
  if(_gains_valid == true && _bounds_valid == true)
    pid_out = _gains.kP * error;
  else
    pid_out = 0;
  
  if (pid_out > _u_bound)
    pid_out = _u_bound;
  if (pid_out > _l_bound)
    pid_out = _l_bound;

  _control_vals->return_val = pid_out;
}

    
