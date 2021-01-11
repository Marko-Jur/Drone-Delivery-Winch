#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "RC_Receiver.h"


//Defining the Receiver object
PulsePositionInput input_values;

//Array for values:
int channel_values[8] = {0,0,0,0,0,0,0,0}; // Right Lateral, Right up/down, Thottle, Left lateral, switch A, switch B, Switch C, Switch D


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

}
