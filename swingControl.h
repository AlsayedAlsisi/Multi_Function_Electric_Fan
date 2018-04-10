/*
 * swingControl.h
 *
 * Created: 02-Apr-18 2:41:51 PM
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
#ifndef SWINGCONTROL_H_
#define SWINGCONTROL_H_


/*----------------------------------------------------------------
--------------------- Public Data Types --------------------------
----------------------------------------------------------------*/
	 typedef enum
	 {
		 SWING_DEGREE0,
		 SWING_DEGREE45,
		 SWING_DEGREE90,
		 SWING_DEGREE135,
		 SWING_DEGREE180,
		 SWING_DEGREE225,
		 SWING_DEGREE270,
		 SWING_DEGREE315,
		 SWING_DEGREE360,
	 }swing_degree_state_t;

/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void swing_control_init(void);
extern void swing_control_update(void);
extern swing_degree_state_t swing_degree_current_state_get(void);
extern void  swing_turn_off(void);
extern void  swing_turn_on(void);


#endif /* SWINGCONTROL_H_ */
/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/