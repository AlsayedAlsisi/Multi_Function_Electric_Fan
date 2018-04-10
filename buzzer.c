/*
 * buzzer.c
 *
 * Created: 06-Apr-18 9:11:59 PM
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
#include "buzzer.h"
#include "gpio.h"
#include "timer0.h"
#include <stdint.h>

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/
#define BUZZER_PORT		PORT_A
#define BUZZER_PIN		PIN_6
#define BUZZ_TIME		2000   //Here the buzz time is chosen as 2000ms = 2 seconds.
/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum{
	BUZZER_WORKING = 0,
	BUZZER_STOPPED
	}buzzer_state_t;

/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static buzzer_state_t buzzer_current_state = BUZZER_STOPPED;
static uint16_t buzzer_time_counter = 0;


/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
	void buzzer_init(void)
	{
		//Initializing the buzzer pin as output, with default state as 0
		gpio_init_port_pin(BUZZER_PORT, BUZZER_PIN, OUTPUT, 0x00); 
	}

	void buzzer_start(void)
	{
		buzzer_current_state = BUZZER_WORKING;
	}
	
	void buzzer_stop(void)
	{
		buzzer_time_counter = 0;
		buzzer_current_state = BUZZER_STOPPED;
	}
	

	void buzzer_update(void)
	{
		switch(buzzer_current_state)
		{
			case BUZZER_WORKING:								//the buzzer is buzzing :D
			gpio_write_port_pin(BUZZER_PORT, BUZZER_PIN, 0xff); //set the buzzer pin as high
			buzzer_time_counter += TIMER_TICK;					//start counting working time
			if (buzzer_time_counter == BUZZ_TIME)				//if the the buzz period has been reached, 
			{
				buzzer_time_counter = 0;						//set the time counter to zero, and
				buzzer_current_state = BUZZER_STOPPED;			//stop the buzzer
			}
			break;
			
			case BUZZER_STOPPED:								//the buzzer is stopped
			gpio_write_port_pin(BUZZER_PORT, BUZZER_PIN, 0x00); //set the buzzer pin as low
			break;
			
			default:
			break;
		}
	}


/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/