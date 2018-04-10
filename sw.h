/*
 * sw.h
 *
 * Created: 05-Mar-18 10:43:56 PM
 * Copyright: ©2018 Alsayed Alsisi
 * Author: Alsayed Alsisi
 * License:
 You have the complete freedom to use the code in any educational or commercial purposes under the following conditions:
 - You don't remove my name under any circumstances.
 - You use the code as is. And if you need to edit it before using it you may contact me first.
 * Contact Details:
 - E-mail: alsayed.alsisi@gmail.com
 - Phone Number: +201066769510
 */ 


#ifndef sw_H_
#define sw_H_

/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/
#include "gpio.h"


/*----------------------------------------------------------------
--------------------- Public Data Types --------------------------
----------------------------------------------------------------*/
typedef enum{
	PRESSED,
	RELEASED,
	FALLING_EDGE,
	RISING_EDGE,
	BOUNCING
	}sw_state_t;


/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void sw_init(void);

extern void sw_update(void);

extern sw_state_t speed_increase_sw_state_get(void);

extern sw_state_t speed_decrease_sw_state_get(void);

extern sw_state_t display_sw_state_get(void);

extern sw_state_t timer_sw_state_get(void);

extern sw_state_t fan_power_sw_state_get(void) ;

#endif /* sw_H_ */