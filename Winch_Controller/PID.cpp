#include "Winch_Libraries.h"
#include "PID.h"

int32_t PID::_u_bound;
int32_t PID::_l_bound;  
int32_t PID::_i_u_bound;
int32_t PID::_i_l_bound;

bool PID::_bounds_valid;
bool PID::_gains_valid;
bool PID::_derivative_valid;

struct gain_vals PID::_gains;
struct control_array * PID::_control_vals;

int32_t PID::_time_step_uS;
double PID::_integrator; 

float PID::_filter_pole;
float PID::_derivative_scale_factor;
double * PID::_filter_memory;
uint8_t PID::_derivative_sample_size;


PID::PID(int32_t l_bound, int32_t u_bound, int32_t integrator_l_bound, int32_t integrator_u_bound, bool anti_windup_state)  {
  Serial.println("Initialization FUCKING WORKS!!! O.O");
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
  Serial.println("Setting constants FUCKING WORKS!!! O.O");
  _gains.kP = kP;
  _gains.kI = kI;
  _gains.kD = kD;
  if((_gains.kP != 0) || (_gains.kI != 0) || (_gains.kD != 0))
    _gains_valid = true;
  else 
    _gains_valid = false;
}


bool PID::begin(float control_freq_Hz, float filter_pole_Rads, uint16_t time_constants, struct control_array * control_vals){
  Serial.println("Begin function FUCKING WORKS!!! O.O");
  if (_gains_valid == false || _bounds_valid == false || control_vals == NULL || filter_pole_Rads == 0){
    return false;
  }
  else{
    Serial.println("Validation FUCKING WORKS!!! O.O");
    _control_vals = control_vals;
    _integrator = 0;
    _time_step_uS = (int32_t)(1000000.0/control_freq_Hz);
    _filter_pole = filter_pole_Rads;
    _derivative_sample_size = (uint8_t)(time_constants * control_freq_Hz / filter_pole_Rads);
    _filter_memory = (double *)malloc(_derivative_sample_size*sizeof(double));
    _derivative_valid = (findScaleFactor() && _filter_memory != NULL);
    
    if(_filter_memory != NULL){
      for (uint8_t i = 0; i < _derivative_sample_size; i++)
        _filter_memory[i] = 0.0;
    }   
    mainLoop.begin(PID::controlLoop, _time_step_uS); 
    return true;
  }
}


void PID::controlLoop() {

  double error = (_control_vals->target_val) - (_control_vals->current_val);
  double exp_factor;
  double derivative_factor;
  double filtered_derivative = 0;
  double pid_out;
  

  for (uint8_t i = 1; i < _derivative_sample_size; i++){
    _filter_memory[i] = _filter_memory[i-1];
  }
  _filter_memory[0] = error;
  
  if (_derivative_valid == true){
    for(uint8_t i = 1; i <_derivative_sample_size; i++){
      exp_factor = (_filter_pole/_derivative_scale_factor)*exp(-1.0*_filter_pole*_time_step_uS*i/1000000.0);
      derivative_factor = (_filter_memory[i-1] - _filter_memory[i])*1000000.0/_time_step_uS;
      filtered_derivative += exp_factor * derivative_factor;
    }
  }
  
  if(_gains_valid == true && _bounds_valid == true)
    pid_out = _gains.kP * error + _gains.kD * filtered_derivative;
  else
    pid_out = 0;
  
  if (pid_out > _u_bound)
    pid_out = _u_bound;
  if (pid_out > _l_bound)
    pid_out = _l_bound;

  _control_vals->return_val = pid_out;
}

bool PID::findScaleFactor(){
  float exp_sum = 0;
  for(uint8_t i = 1; i <= _derivative_sample_size; i++){
    exp_sum += (_time_step_uS/1000000.0)*_filter_pole*exp(-1.0*_filter_pole*_time_step_uS*i/1000000.0);
  }
  if (exp_sum >= 0.4){
    _derivative_scale_factor = exp_sum;
    return true;
  }
  else
    return false;
}



    
