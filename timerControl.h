/*
 * timerControl.h
 *
 * Created: 06-Apr-18 8:20:22 PM
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
#ifndef TIMERCONTROL_H_
#define TIMERCONTROL_H_

/*----------------------------------------------------------------
--------------------- File Inclusion -----------------------------
----------------------------------------------------------------*/
#include <stdint.h>


/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void    timer_control_update(void);
extern uint8_t timer_control_minutes_counter_value_get(void);
extern uint8_t timer_control_hours_counter_value_get(void);
extern void    timer_control_stop(void);
extern void    timer_control_start(void);

#endif /* TIMERCONTROL_H_ */
/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/