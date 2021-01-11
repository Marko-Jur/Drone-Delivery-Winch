#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Winch_Setup.h"


//Declaring objects
Servo brake_servo;
Servo motor;


/*Function: Winch Setup
 *Author: Marko Jurisic
 *Input Parameters: None
 *Output Parameters: None
 *
 *Purpose: Sets up the Actuator and Motor
 * 
 */
void motorSetup(){


//Setup the Linear actuaotr
  brake_servo.attach(BRAKE_SERVO_PIN);

//Setup the motor:
  motor.attach(REEL_MOTOR_PIN);
  motor.writeMicroseconds(MOTOR_STOP);
  delay(1000);
  motor.writeMicroseconds(MOTOR_MAX);
  delay(1000);

}