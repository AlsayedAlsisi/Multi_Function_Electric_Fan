/*
 * speedControl.h
 *
 * Created: 01-Apr-18 11:22:55 PM
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
#ifndef SPEEDCONTROL_H_
#define SPEEDCONTROL_H_


/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Constants ---------------------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Data Types --------------------------
----------------------------------------------------------------*/
typedef enum{
	SPEED_MIN = 0,
	SPEED_MID,
	SPEED_MAX,
	SPEED_STOPPED,
	SPEED_START
	}speed_state_t;

/*----------------------------------------------------------------
--------------------- Public Variable Declarations ---------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void speed_control_init(void);
extern void speed_control_update(void);
extern void speed_motor_turn_off(void);
extern void speed_motor_turn_on(void);
extern speed_state_t speed_current_state_get(void);


#endif /* SPEEDCONTROL_H_ */
/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/




