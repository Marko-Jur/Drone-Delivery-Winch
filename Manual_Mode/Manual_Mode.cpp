#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Manual_Mode.h"

//Defining the Receiver object
PulsePositionInput input_values;

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

//Declaring Servo object
Servo brake_servo;
Servo motor;


/*Function: RC Setup
 *Author: Marko Jurisic
 *Input Parameters: None
 *Output Parameters: None
 *
 *Purpose: Sets up the receiver
 * 
 */
void rcSetup(){

//Set up the Receiver
 input_values.begin(RCRX);

//Setup the Linear actuaotr
  brake_servo.attach(BRAKE_SERVO_PIN);

//Setup the motor:
  motor.attach(REEL_MOTOR_PIN);
  motor.writeMicroseconds(MOTOR_STOP);
  delay(1000);
  motor.writeMicroseconds(MOTOR_MAX);
  delay(1000);

}


/*Function: RC Reader
 *Author: Marko Jurisic
 *Input Parameters: An array of steering values
 *Output Parameters: Modifies the input array with values from the transmitter
 *
 *Purpose: Getting values from the transmitter to steer Wall-E
 * 
 */
void rcReader(int channel_values[]){



channel_values[0] = input_values.read(1);
channel_values[1] = input_values.read(2);
channel_values[2] = input_values.read(3);
channel_values[3] = input_values.read(4);
channel_values[4] = input_values.read(5);
channel_values[5] = input_values.read(6);
channel_values[6] = input_values.read(7);
channel_values[7] = input_values.read(8);

//Uncomment for serial monitor number

/*
Serial.print(channel_values[0]);Serial.print("\t");
Serial.print(channel_values[1]);Serial.print("\t");
Serial.print(channel_values[2]);Serial.print("\t");
Serial.print(channel_values[3]);Serial.print("\t");
Serial.print(channel_values[4]);Serial.print("\t");
Serial.print(channel_values[5]);Serial.print("\t");
Serial.print(channel_values[6]);Serial.print("\t");
Serial.print(channel_values[7]);Serial.print("\t");
Serial.println("");
*/

delay(1);

}

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
