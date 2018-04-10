/*
 * timer.h
 *
 *	Created: 02-Mar-18 11:15:34 PM
 *  Author: Alsayed Alsisi
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


#ifndef TIMER0_H_
#define TIMER0_H_

/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/
#include <stdint.h>

/*----------------------------------------------------------------
--------------------- Public Constants --------------------------
----------------------------------------------------------------*/
#define TIMER_TICK  10    //the timer in this project generates interrupts each 5ms



/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void timer0_init(void);
extern void timer0_start(void);


#endif /* TIMER0_H_ */