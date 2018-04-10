/*
 * fanPowerControl.c
 *
 * Created: 08-Apr-18 6:47:48 PM
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
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/
#include "fanPowerControl.h"
#include "timerControl.h"
#include "buzzer.h"
#include "sw.h"
#include "timer0.h"
#include "lcd4bit.h"
#include "swingControl.h"
#include "speedControl.h"
#include "ssd.h"

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum
{
	FAN_ON = 0,
	FAN_OFF
	}fan_state_t;
/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static fan_state_t fan_current_state = FAN_ON;

/*----------------------------------------------------------------
--------------------- Public Variable Definitions ----------------
----------------------------------------------------------------*/

/*----------------------------------------------------------------
--------------------- Private Functions Prototypes ---------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
 void fan_turn_off(void)
{
	buzzer_start();
	//turn off all the peripherals of the fan:
	speed_motor_turn_off();
	swing_turn_off();
	timer_control_stop();
	lcd_turn_off();
	ssd_turn_off();
	
}
 void fan_turn_on(void)
{
	//turn on all the peripherals of the fan:
	buzzer_start();
	speed_motor_turn_on();
	swing_turn_on();
	timer_control_start();
	lcd_turn_on();
	ssd_turn_on();
}

void fan_power_update()
{
	switch (fan_current_state)
	{
		case FAN_ON:
		if (fan_power_sw_state_get() == FALLING_EDGE)		//if the sw is pressed, then
		{
			fan_current_state = FAN_OFF;
			fan_turn_off();
		}
		break;	
		
		case FAN_OFF:
		if (fan_power_sw_state_get() == FALLING_EDGE)		//if the sw is pressed, then
		{
			fan_current_state = FAN_ON;
			fan_turn_on();
		}
		break;
		
		default:
		break;
	}
	
}

/*----------------------------------------------------------------
--------------------- Private Functions Definitions --------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/