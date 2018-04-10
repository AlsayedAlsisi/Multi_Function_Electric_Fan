/*
 * swingControl.c
 *
 * Created: 02-Apr-18 2:40:52 PM
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
#include "swingControl.h"
#include "gpio.h"
#include "adc.h"
#include "buzzer.h"

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/
#define SWING_MOTOR_PORT		PORT_B

#define SWING_MOTOR_PIN_0		PIN_0				
#define SWING_MOTOR_PIN_1		PIN_1
#define SWING_MOTOR_PIN_2		PIN_2
#define SWING_MOTOR_PIN_3		PIN_3

#define SWING_SLIDER_CHANNEL	ADC_CHANNEL_0

/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum
{
	SWING_WORKING = 0,
	SWING_STOPPED
	}swing_state_t;
/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
//To control whether the swing is working or stopped:
static swing_state_t swing_state = SWING_WORKING; 

//to store the current rotation degree state:
static swing_degree_state_t swing_degree_current_state = SWING_DEGREE0; 

/*the following variable was created to store the previous degree state, so that when the current state..
	changes and the code compares it with the previous state, it can tell whether the state has changed or not.
	If yes, it starts the buzzer.*/
static swing_degree_state_t swing_degree_previous_state = SWING_DEGREE0;


/*----------------------------------------------------------------
--------------------- Private Functions Prototypes ---------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
 void swing_control_init(void)
{
	gpio_init_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), OUTPUT, 0X00);
	
	swing_degree_previous_state = ((adc_read_channel(SWING_SLIDER_CHANNEL)/113)); // 1023/(9 degree states) = 113
	if (swing_degree_current_state != 0)
	{swing_degree_previous_state -=1;}
}
 void swing_control_update(void)
{
	
	
	
	switch (swing_state)
	{
		case SWING_WORKING:
		swing_degree_current_state = ((adc_read_channel(SWING_SLIDER_CHANNEL)/113)); // 1023/(9 degree states) = 113
		if (swing_degree_current_state != 0)
		{swing_degree_current_state -=1;}
			
		if(swing_degree_current_state != swing_degree_previous_state)
		{
			buzzer_start();
		}
		break;
		
		case SWING_STOPPED:
		swing_degree_current_state = SWING_DEGREE0; 
		break;
		
		default:
		break;
	}
	
	switch (swing_degree_current_state)
	{
		case SWING_DEGREE0:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000000);
		break;
		
		case SWING_DEGREE45:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000001);
		break;
		
		case SWING_DEGREE90:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000010);
		break;
		
		case SWING_DEGREE135:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000011);
		break;
		
		case SWING_DEGREE180:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000100);
		break;
		
		case SWING_DEGREE225:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000101);
		break;
		
		case SWING_DEGREE270:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000110);
		break;
		
		case SWING_DEGREE315:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00000111);
		break;
		
		case SWING_DEGREE360:
		gpio_write_port_pin(SWING_MOTOR_PORT,  (SWING_MOTOR_PIN_3|SWING_MOTOR_PIN_2|SWING_MOTOR_PIN_1|SWING_MOTOR_PIN_0), 0b00001000);
		break;
		
		default:
		break;
	}
	
	swing_degree_previous_state = swing_degree_current_state;
}

 swing_degree_state_t swing_degree_current_state_get(void)
 {
	 return swing_degree_current_state;
 }
 
 void  swing_turn_off(void)
 {
	swing_state = SWING_STOPPED; 
 }
 
 void  swing_turn_on(void)
{
	swing_state = SWING_WORKING;
}

/*----------------------------------------------------------------
--------------------- Private Functions Definitions --------------
----------------------------------------------------------------*/


/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/