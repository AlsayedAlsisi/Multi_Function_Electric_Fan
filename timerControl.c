/*
 * timerControl.c
 *
 * Created: 06-Apr-18 8:20:04 PM
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
#include "timerControl.h"
#include "buzzer.h"
#include "sw.h"
#include "timer0.h"
#include "lcd4bit.h"
#include "swingControl.h"
#include "fanPowerControl.h"
#include "ssd.h"
#include <stdint.h>

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum{
	NO_STOP,				//the state in which the fan is working continuously without time limit.
	TURN_OFF_AFTER_1HOUR,	//the state in which the fan will stop after 1 hour.
	TURN_OFF_AFTER_2HOUR,	//the state in which the fan will stop after 2 hours.
	TURN_OFF_AFTER_4HOUR,	//the state in which the fan will stop after 4 hours.
	TIMER_CONTROL_STOPPED				//the state in which the fan is stopped.
} timer_control_state_t;


/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static timer_control_state_t timer_control_current_state = NO_STOP; //fan default state is working continuously.
static uint16_t timer_milliseconds_counter = 0;
static uint8_t  timer_seconds_couter  = 0;
static uint8_t  timer_minutes_counter = 0;
static uint8_t  timer_hours_counter   = 0;

/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
void timer_control_update(void)
{
	sw_state_t timer_control_sw_state = timer_sw_state_get(); //reading the state of the timer control sw
	switch (timer_control_current_state)
	{
		case NO_STOP:
		//keep checking for a press on timer control sw:
		if (timer_control_sw_state == FALLING_EDGE)				//if the sw is pressed, then
		{
			buzzer_start();										//start the 2 seconds buzz, and
			timer_control_current_state = TURN_OFF_AFTER_1HOUR; //go to next state.
			ssd_minutes_var_set(0);
			ssd_hours_var_set(1);
		}
		break;
		
		
		case TURN_OFF_AFTER_1HOUR:
		timer_milliseconds_counter +=TIMER_TICK; //start counting time
		if(timer_milliseconds_counter == 1000)
		{
			timer_milliseconds_counter = 0;
			timer_seconds_couter++;
			if (timer_seconds_couter == 60)
			{
				timer_seconds_couter = 0;
				timer_minutes_counter++;
				if (timer_minutes_counter == 1)
				{ssd_hours_var_decrement();}
				if (timer_minutes_counter == 60)
				{
					timer_minutes_counter = 0;
					timer_hours_counter++;
				}
			}
		}
		
		if (timer_hours_counter == 1)
		{
			timer_hours_counter = 0;
			fan_turn_off();
		}
		//keep checking for a press on timer control sw:
		else if (timer_control_sw_state == FALLING_EDGE)		//if the sw is pressed, then
		{
			buzzer_start();										//start the 2 seconds buzz, and
			timer_control_current_state = TURN_OFF_AFTER_2HOUR; //go to next state.
			timer_seconds_couter  = 0;
			timer_minutes_counter = 0;
			timer_hours_counter   = 0;
			ssd_minutes_var_set(0);
			ssd_hours_var_set(2);
		}
		break;
		
		
		case TURN_OFF_AFTER_2HOUR:
		timer_milliseconds_counter +=TIMER_TICK; //start counting time
		if(timer_milliseconds_counter == 1000)
		{
			timer_milliseconds_counter = 0;
			timer_seconds_couter++;
			if (timer_seconds_couter == 60)
			{
				timer_seconds_couter = 0;
				timer_minutes_counter++;
				if (timer_minutes_counter == 1)
				{ssd_hours_var_decrement();}
				if (timer_minutes_counter == 60)
				{
					timer_minutes_counter = 0;
					timer_hours_counter++;
				}
			}
		}
		
		if (timer_hours_counter == 2)
		{
			timer_hours_counter = 0;
			fan_turn_off();
		}
		//keep checking for a press on timer control sw:
		else if (timer_control_sw_state == FALLING_EDGE)			//if the sw is pressed, then
		{
			buzzer_start();											//start the 2 seconds buzz, and
			timer_control_current_state = TURN_OFF_AFTER_4HOUR;		//go to next state.
			timer_seconds_couter  = 0;
			timer_minutes_counter = 0;
			timer_hours_counter   = 0;
			ssd_minutes_var_set(0);
			ssd_hours_var_set(4);
		}
		break;
		
		case TURN_OFF_AFTER_4HOUR:
		timer_milliseconds_counter +=TIMER_TICK; //start counting time
		if(timer_milliseconds_counter == 1000)
		{
			timer_milliseconds_counter = 0;
			timer_seconds_couter++;
			if (timer_seconds_couter == 60)
			{
				timer_seconds_couter = 0;
				timer_minutes_counter++;
				if (timer_minutes_counter == 1)
				{ssd_hours_var_decrement();}
				if (timer_minutes_counter == 60)
				{
					timer_minutes_counter = 0;
					timer_hours_counter++;
					
				}
			}
		}
		if (timer_hours_counter == 4)
		{
			timer_hours_counter = 0;
			fan_turn_off();
		}
		//keep checking for a press on timer control sw:
		else if (timer_control_sw_state == FALLING_EDGE)//if the sw is pressed,
		{
			timer_control_current_state = NO_STOP; //go again  to the start state
			timer_seconds_couter  = 0;
			timer_minutes_counter = 0;
			timer_hours_counter   = 0;
			buzzer_start(); //starting the 2 seconds buzz
			ssd_minutes_var_set(0);
			ssd_hours_var_set(0);
		}
		break;
		
		case TIMER_CONTROL_STOPPED:
		timer_seconds_couter  = 0;
		timer_minutes_counter = 0;
		timer_hours_counter   = 0;
		ssd_minutes_var_set(0);
		ssd_hours_var_set(0);
		break;
		
		default:
		break;
	}
	
}

 
 uint8_t  timer_control_minutes_counter_value_get(void)
 {
	 return timer_minutes_counter;
 }
 
 uint8_t timer_control_hours_counter_value_get(void)
 {
	 return timer_hours_counter;
 }

extern void    timer_control_stop(void)
{
	timer_control_current_state = TIMER_CONTROL_STOPPED;
}

extern void    timer_control_start(void)
{
	timer_control_current_state = NO_STOP;
}

/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/