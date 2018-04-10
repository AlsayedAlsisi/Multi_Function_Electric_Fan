/*
 * sw.c
 *
 * Created: 05-Mar-18 10:44:11 PM
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
#include "gpio.h"
#include "sw.h"

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/
#define SPEED_INCREASE_SW_PORT 		    PORT_A
#define SPEED_INCREASE_SW_PIN           PIN_1

#define SPEED_DECREASE_SW_PORT 			PORT_A
#define SPEED_DECREASE_SW_PIN           PIN_2

#define DISPLAY_SW_PORT 		        PORT_A
#define DISPLAY_SW_PIN                  PIN_3

#define TIMER_SET_SW_PORT 		        PORT_A
#define TIMER_SET_SW_PIN                PIN_4

#define FAN_POWER_SW_PORT 		        PORT_A
#define FAN_POWER_SW_PIN                PIN_5


/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum 
{
	LEVEL_LOW, 
	LEVEL_HIGH,
	LEVEL_BOUNCING
	}level_t;
/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static sw_state_t 	speed_increase_sw_state = RELEASED;
static sw_state_t 	speed_decrease_sw_state = RELEASED;
static sw_state_t 	display_sw_state = RELEASED;
static sw_state_t 	timer_sw_state = RELEASED;
static sw_state_t 	fan_power_sw_state = RELEASED;


/*----------------------------------------------------------------
--------------------- Private Functions Prototypes ---------------
----------------------------------------------------------------*/
static void speed_increase_sw_state_update(void);
static void speed_decrease_sw_state_update(void);
static void display_sw_state_update(void);
static void timer_sw_state_update(void);
static void fan_power_sw_state_update(void);

/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
void sw_init(void)
{
	
	gpio_init_port_pin(SPEED_INCREASE_SW_PORT,   SPEED_INCREASE_SW_PIN,   INPUT, 0xff); //initializing and enabling the pull-up resistor of the sw pin
	gpio_init_port_pin(SPEED_DECREASE_SW_PORT,   SPEED_DECREASE_SW_PIN,   INPUT, 0xff); //initializing and enabling the pull-up resistor of the sw pin
	gpio_init_port_pin(DISPLAY_SW_PORT,                 DISPLAY_SW_PIN,   INPUT, 0xff); //initializing and enabling the pull-up resistor of the sw pin
	gpio_init_port_pin(TIMER_SET_SW_PORT,             TIMER_SET_SW_PIN,   INPUT, 0xff); //initializing and enabling the pull-up resistor of the sw pin
	gpio_init_port_pin(FAN_POWER_SW_PORT ,            FAN_POWER_SW_PIN,   INPUT, 0xff); //initializing and enabling the pull-up resistor of the sw pin
}

void sw_update(void) //This function should be called each 10ms, for example in a timer interrupt.
{
	speed_increase_sw_state_update();
	speed_decrease_sw_state_update();
	display_sw_state_update();
	timer_sw_state_update();
	fan_power_sw_state_update();
	
}


sw_state_t speed_increase_sw_state_get(void) //This function is called at most one time each 10ms to check the switch state.
{
	return	speed_increase_sw_state  ;
}

sw_state_t speed_decrease_sw_state_get(void) //This function is called at most one time each 10ms to check the switch state.
{
	return speed_decrease_sw_state  ;
}

sw_state_t display_sw_state_get(void) //This function is called at most one time each 10ms to check the switch state.
{
	 return display_sw_state ;
}

sw_state_t timer_sw_state_get(void) //This function is called at most one time each 10ms to check the switch state.
{
	return timer_sw_state  ;
}

 sw_state_t fan_power_sw_state_get(void) //This function is called at most one time each 10ms to check the switch state.
{
	return fan_power_sw_state;
}





/*----------------------------------------------------------------
--------------------- Private Functions Definitions --------------
----------------------------------------------------------------*/
static void speed_increase_sw_state_update(void)
{
	static uint8_t sw_samples[5] = {1,1,1,1,1};
	static level_t previous_level = LEVEL_HIGH;
	static level_t current_level  = LEVEL_HIGH;
	
	sw_samples[0] = sw_samples[1];
	sw_samples[1] = sw_samples[2];
	sw_samples[2] = sw_samples[3];
	sw_samples[3] = sw_samples[4];
	sw_samples[4] = gpio_read_port_pin(SPEED_INCREASE_SW_PORT,   SPEED_INCREASE_SW_PIN)>>1;
	
	//Checking what current level of the sw it is:
	if (sw_samples[0] == 1 && sw_samples[1] == 1 && sw_samples[2] == 1 && sw_samples[3] == 1 && sw_samples[4] == 1)
	{current_level = LEVEL_HIGH;}
	
	else if (sw_samples[0] == 0 && sw_samples[1] == 0 && sw_samples[2] == 0 && sw_samples[3] == 0 && sw_samples[4] == 0)
	{current_level = LEVEL_LOW;}
	
	
	//Checking what current state of the sw it is:
	if (previous_level == LEVEL_HIGH && current_level == LEVEL_HIGH)
	{
		speed_increase_sw_state = RELEASED;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_LOW)
	{
		speed_increase_sw_state = PRESSED;
	}
	else if (previous_level == LEVEL_HIGH && current_level == LEVEL_LOW)
	{
		speed_increase_sw_state = FALLING_EDGE;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_HIGH)
	{
		speed_increase_sw_state = RISING_EDGE;
	}

	
	
	previous_level = current_level;
}


static void speed_decrease_sw_state_update(void)
{
	static uint8_t sw_samples[5] = {1,1,1,1,1};
	static level_t previous_level = LEVEL_HIGH;
	static level_t current_level  = LEVEL_HIGH;
	
	sw_samples[0] = sw_samples[1];
	sw_samples[1] = sw_samples[2];
	sw_samples[2] = sw_samples[3];
	sw_samples[3] = sw_samples[4];
	sw_samples[4] = gpio_read_port_pin(SPEED_DECREASE_SW_PORT,   SPEED_DECREASE_SW_PIN)>>2;
	
	//Checking what current level of the sw it is:
	if (sw_samples[0] == 1 && sw_samples[1] == 1 && sw_samples[2] == 1 && sw_samples[3] == 1 && sw_samples[4] == 1)
	{current_level = LEVEL_HIGH;}
	
	else if (sw_samples[0] == 0 && sw_samples[1] == 0 && sw_samples[2] == 0 && sw_samples[3] == 0 && sw_samples[4] == 0)
	{current_level = LEVEL_LOW;}
	
	
	//Checking what current state of the sw it is:
	if (previous_level == LEVEL_HIGH && current_level == LEVEL_HIGH)
	{
		speed_decrease_sw_state = RELEASED;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_LOW)
	{
		speed_decrease_sw_state = PRESSED;
	}
	else if (previous_level == LEVEL_HIGH && current_level == LEVEL_LOW)
	{
		speed_decrease_sw_state = FALLING_EDGE;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_HIGH)
	{
		speed_decrease_sw_state = RISING_EDGE;
	}

	
	
	previous_level = current_level;
}


static void display_sw_state_update(void)
{
	static uint8_t sw_samples[5] = {1,1,1,1,1};
	static level_t previous_level = LEVEL_HIGH;
	static level_t current_level  = LEVEL_HIGH;
	
	sw_samples[0] = sw_samples[1];
	sw_samples[1] = sw_samples[2];
	sw_samples[2] = sw_samples[3];
	sw_samples[3] = sw_samples[4];
	sw_samples[4] = gpio_read_port_pin(DISPLAY_SW_PORT, DISPLAY_SW_PIN)>>3;
	
	//Checking what current level of the sw it is:
	if (sw_samples[0] == 1 && sw_samples[1] == 1 && sw_samples[2] == 1 && sw_samples[3] == 1 && sw_samples[4] == 1)
	{current_level = LEVEL_HIGH;}
	
	else if (sw_samples[0] == 0 && sw_samples[1] == 0 && sw_samples[2] == 0 && sw_samples[3] == 0 && sw_samples[4] == 0)
	{current_level = LEVEL_LOW;}
	
	
	//Checking what current state of the sw it is:
	if (previous_level == LEVEL_HIGH && current_level == LEVEL_HIGH)
	{
		display_sw_state = RELEASED;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_LOW)
	{
		display_sw_state = PRESSED;
	}
	else if (previous_level == LEVEL_HIGH && current_level == LEVEL_LOW)
	{
		display_sw_state = FALLING_EDGE;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_HIGH)
	{
		display_sw_state = RISING_EDGE;
	}

	
	
	previous_level = current_level;
}


static void timer_sw_state_update(void)
{
	static uint8_t sw_samples[5] = {1,1,1,1,1};
	static level_t previous_level = LEVEL_HIGH;
	static level_t current_level  = LEVEL_HIGH;
	
	sw_samples[0] = sw_samples[1];
	sw_samples[1] = sw_samples[2];
	sw_samples[2] = sw_samples[3];
	sw_samples[3] = sw_samples[4];
	sw_samples[4] = gpio_read_port_pin(TIMER_SET_SW_PORT, TIMER_SET_SW_PIN)>>4;
	
	//Checking what current level of the sw it is:
	if (sw_samples[0] == 1 && sw_samples[1] == 1 && sw_samples[2] == 1 && sw_samples[3] == 1 && sw_samples[4] == 1)
	{current_level = LEVEL_HIGH;}
	
	else if (sw_samples[0] == 0 && sw_samples[1] == 0 && sw_samples[2] == 0 && sw_samples[3] == 0 && sw_samples[4] == 0)
	{current_level = LEVEL_LOW;}
	
	
	//Checking what current state of the sw it is:
	if (previous_level == LEVEL_HIGH && current_level == LEVEL_HIGH)
	{
		timer_sw_state = RELEASED;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_LOW)
	{
		timer_sw_state = PRESSED;
	}
	else if (previous_level == LEVEL_HIGH && current_level == LEVEL_LOW)
	{
		timer_sw_state = FALLING_EDGE;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_HIGH)
	{
		timer_sw_state = RISING_EDGE;
	}

	
	
	previous_level = current_level;
}


static void fan_power_sw_state_update(void)
{
	static uint8_t sw_samples[5] = {1,1,1,1,1};
	static level_t previous_level = LEVEL_HIGH;
	static level_t current_level  = LEVEL_HIGH;
	
	sw_samples[0] = sw_samples[1];
	sw_samples[1] = sw_samples[2];
	sw_samples[2] = sw_samples[3];
	sw_samples[3] = sw_samples[4];
	sw_samples[4] = gpio_read_port_pin(FAN_POWER_SW_PORT , FAN_POWER_SW_PIN)>>5;
	
	//Checking what current level of the sw it is:
	if (sw_samples[0] == 1 && sw_samples[1] == 1 && sw_samples[2] == 1 && sw_samples[3] == 1 && sw_samples[4] == 1)
	{current_level = LEVEL_HIGH;}
	
	else if (sw_samples[0] == 0 && sw_samples[1] == 0 && sw_samples[2] == 0 && sw_samples[3] == 0 && sw_samples[4] == 0)
	{current_level = LEVEL_LOW;}
	
	
	//Checking what current state of the sw it is:
	if (previous_level == LEVEL_HIGH && current_level == LEVEL_HIGH)
	{
		fan_power_sw_state = RELEASED;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_LOW)
	{
		fan_power_sw_state = PRESSED;
	}
	else if (previous_level == LEVEL_HIGH && current_level == LEVEL_LOW)
	{
		fan_power_sw_state = FALLING_EDGE;
	}
	else if (previous_level == LEVEL_LOW && current_level == LEVEL_HIGH)
	{
		fan_power_sw_state = RISING_EDGE;
	}

	
	
	previous_level = current_level;
}


/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/