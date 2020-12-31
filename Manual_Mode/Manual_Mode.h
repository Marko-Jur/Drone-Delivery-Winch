/* Pin Assignments
 *  
 *  Created by: Marko Jurisic

 *  Purpose: Contains function declarations for manual mode
 */

#ifndef _MANUALMODE_H    
#define _MANUALMODE_H    

void rcSetup();
void rcReader(int channel_values[]);
void manualMotorController(int channel_values[]);

#endif
