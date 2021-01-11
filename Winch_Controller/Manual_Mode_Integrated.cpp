#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Manual_Mode_Integrated.h"

//Array for values:
int channel_values[8] = {0,0,0,0,0,0,0,0}; // Right Lateral, Right up/down, Thottle, Left lateral, switch A, switch B, Switch C, Switch D
int mapped_channel_values[8] = {0,0,0,0,0,0,0,0}; // Mapped values from 1000-2000 to 0-255

//Switch values to Arm
const int PRIMARY_ARM = 1500;
const int MOTOR_ARM = 1800;

//Ranges
int ACTUATOR_MAX = 1000;
int ACTUATOR_MIN = 2000;
int MOTOR_STOP = 1000;
int MOTOR_MAX = 2000;

//Values
int actuator_position = 0;
int motor_speed = 0;

void manualMotorController(int channel_values[]){

  

  //Winch is armed, allow the control of the brake or the motor depending on the Motor arm switch
  if (channel_values[4] > PRIMARY_ARM){
    //Motor is disarmed, we know control the servo for descent
    //Serial.println("Armed");
    if(channel_values[5] < MOTOR_ARM){
      actuator_position = map(channel_values[2],1000,2000,ACTUATOR_MIN,ACTUATOR_MAX);
      brake_servo.writeMicroseconds(actuator_position);
      motor.writeMicroseconds(MOTOR_STOP);
      //Serial.println("Motor Disarmed");
    }

    //Motor is armed, brake is completely released and we know control the motor. While using make sure to wait for the brake to completely retract before reeling
    else{
      brake_servo.writeMicroseconds(ACTUATOR_MAX);
      motor.writeMicroseconds(channel_values[2]);
      Serial.println("MotorArmed");
    }
  }

//Winch is not armed, open the brake and stop the motor
  else{
    motor.writeMicroseconds(MOTOR_STOP);
    brake_servo.writeMicroseconds(ACTUATOR_MAX);
  }

}