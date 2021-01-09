#ifndef _PID_H
#define _PID_H

//structures 

typedef struct gain_vals{
  float kP;
  float kI;
  float kD;
  float kU;
} gain_vals;

typedef struct control_array{
  double return_val;
  double target_val;
  double current_val;
}control_array;


//class declarations:

class PID {
public:
  PID(int32_t u_bound, int32_t l_bound, int32_t integrator_u_bound, int32_t integrator_l_bound, bool anti_windup_state);
  void setConstants(float kP, float kI, float kD);
  bool begin(float control_freq_Hz, float filter_pole_Rads, uint16_t time_constants, struct control_array * control_vals);
  bool findScaleFactor();
  static void controlLoop();
  
private:
  static int32_t _u_bound;
  static int32_t _l_bound;  
  static int32_t _i_u_bound;
  static int32_t _i_l_bound;

  static int32_t _time_step_uS;
  
  static struct gain_vals _gains;
  static struct control_array * _control_vals;
  
  static bool _bounds_valid;
  static bool _gains_valid;
  static bool _derivative_valid;
  
  static double _integrator; 

  static float _filter_pole;
  static float _derivative_scale_factor;
  static double * _filter_memory;
  static uint8_t _derivative_sample_size;

  IntervalTimer mainLoop;
  
};


#endif 
