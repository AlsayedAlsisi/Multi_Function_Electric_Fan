/*
 * buzzer.h
 *
 * Created: 06-Apr-18 9:11:47 PM
 * Copyright:  ©2018 Alsayed Alsisi
 * Author: Alsayed Alsisi
 * License:
 You have the complete freedom to use the code in any educational or commercial purposes under the following conditions:
 - You don't remove my name under any circumstances.
 - You use the code as is. And if you need to edit it before using it you may contact me first.
 * Contact Details:
 - E-mail: alsayed.alsisi@gmail.com
 - Phone Number: +201066769510
 */ 

/*----------------------------------------------------------------
--------------------- Header Guard -------------------------------
----------------------------------------------------------------*/
#ifndef BUZZER_H_
#define BUZZER_H_


/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Constants ---------------------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Data Types --------------------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- Public Variable Declarations ---------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void buzzer_init(void);
extern void buzzer_start(void);
extern void buzzer_stop(void);
extern void buzzer_update(void);
#endif /* BUZZER_H_ */
/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/



