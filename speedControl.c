/*
 * speedControl.c
 *
 * Created: 01-Apr-18 11:22:34 PM
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
#include "speedControl.h"
#include "timer2.h"
#include "timer0.h"
#include "gpio.h"
#include "sw.h"
#include "buzzer.h"
#include <avr/interrupt.h>

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/
#define SPEED_MOTOR_PORT		PORT_B
#define SPEED_MOTOR_PIN			PIN_4

/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum
{
	PULSE_ON=0,
	PULSE_OFF
	}pulse_t;
/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static speed_state_t speed_current_state = SPEED_START;
static pulse_t pulse = PULSE_ON;

/*----------------------------------------------------------------
--------------------- Private Functions Prototypes ---------------
----------------------------------------------------------------*/



/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
 void speed_control_init(void)
{
	gpio_init_port_pin(SPEED_MOTOR_PORT, SPEED_MOTOR_PIN, OUTPUT, 0x00);		
	
	// 10ms / 180degree = 55us/1degree --> OCR2 = (55 * 170degree) / T - 1 ~= 145, at 16MHZ system clock freq.
	timer2_load_ocr2(145);	//145 is the value to load to achieve a pulse at the starting degree of the motor.
	timer2_start();			//starting the timer
}
 void speed_control_update(void)
 {
	 static uint8_t degree_counter = 170;
	 static uint8_t time_counter = 0;
	 static uint8_t value_to_load;
	 switch (speed_current_state)
	 { 
		 case SPEED_MIN:	 
		 timer2_load_ocr2(value_to_load);	
		 timer2_start();
		 if (degree_counter>120)
		 {
			 time_counter +=TIMER_TICK;
			 if (time_counter == 80)
			 {
				 time_counter = 0;
				 degree_counter--;
				 value_to_load = (((degree_counter * 55) / 64)-1);	// T = 1 / timer freq. = 1 /(1024/16MHZ) = 64us
			 }
		 }
		 else if (degree_counter<120)
		 {
			 time_counter +=TIMER_TICK;
			 if (time_counter == 80)
			 {
				 time_counter = 0;
				 degree_counter++;
				 value_to_load = (((degree_counter * 55) / 64)-1);
			 }
		 }
		 else
		value_to_load = 119;
		 if (speed_increase_sw_state_get() == FALLING_EDGE)
		 {
			 buzzer_start();
			 speed_current_state = SPEED_MID; //If the + sw is pressed, go to next state.
		 }
		 break;
		 
		 case SPEED_MID:
		 timer2_load_ocr2(value_to_load);	
		 timer2_start();
		 if (degree_counter>90)
		 {
			 time_counter +=TIMER_TICK;
			 if (time_counter == 80)
			 {
				 time_counter = 0;
				 degree_counter--;
				 value_to_load = (((degree_counter * 55) / 64)-1);	// T = 1 / timer freq. = 1 /(1024/16MHZ) = 64us
			 }
		 }
		 else if (degree_counter<90)
		 {
			 time_counter +=TIMER_TICK;
			 if (time_counter == 80)
			 {
				 time_counter = 0;
				 degree_counter++;
				 value_to_load = (((degree_counter * 55) / 64)-1);
			 }
		 }
		 else
		 value_to_load = 76;				// 10ms/180degree = 55 us/degree--> OCR = (55 * 90degree) / T - 1 ~= 76, at 16MHZ system clock freq.
		 if (speed_increase_sw_state_get() == FALLING_EDGE)
		 {
			 buzzer_start();
			 speed_current_state = SPEED_MAX; //If the + sw is pressed, go to next state.
		 }
		 if (speed_decrease_sw_state_get() == FALLING_EDGE)
		 {
			 buzzer_start();
			 speed_current_state = SPEED_MIN; //If the - sw is pressed, go to previous state.
		 }
		 break;
		 
		 
		 case SPEED_MAX:
		 timer2_load_ocr2(value_to_load);	// T = 1 / timer freq. = 1 /(1024/16MHZ) = 64us
		 timer2_start();
		 if (degree_counter>10)
		 {
			 time_counter +=TIMER_TICK;
			 if (time_counter == 80)
			 {
				 time_counter = 0;
				 degree_counter--;
				 value_to_load = (((degree_counter * 55) / 64)-1);
			 }
		 }
		 else
		value_to_load= 8; // 10ms/180degree = 55 us/degree--> OCR = (55 * 10degree) / T - 1 ~= 8, at 16MHZ system clock freq.
		 if (speed_decrease_sw_state_get() == FALLING_EDGE)
		 {
			 buzzer_start();
			 speed_current_state = SPEED_MID; //If the - sw is pressed, go to previous state.
		 }
		 break;
		 
		 case SPEED_STOPPED:
		 timer2_stop();
		 break;
		 
		 case SPEED_START:
		 degree_counter = 170;
		 time_counter = 0;
		 value_to_load = 145;
		 speed_current_state = SPEED_MIN;
		 break;
		 
		 default:
		 break;
	 }
	 
 }

 void speed_motor_turn_off(void)
{
	 speed_current_state = SPEED_STOPPED;
}
 void speed_motor_turn_on(void)
{
	speed_current_state = SPEED_START;
}

 speed_state_t speed_current_state_get(void)
 {
	 return speed_current_state;
 }


/*----------------------------------------------------------------
--------------------- Private Functions Definitions --------------
----------------------------------------------------------------*/
ISR(TIMER2_COMP_vect)
{
	// generating a 100 microSecond pulse on the pin connected to the triac:
	switch(pulse)
	{
	case PULSE_ON:
	gpio_write_port_pin(SPEED_MOTOR_PORT, SPEED_MOTOR_PIN, 0xff);
	timer2_load_ocr2(1);
	pulse = PULSE_OFF;
	break;
	
	case PULSE_OFF:
	gpio_write_port_pin(SPEED_MOTOR_PORT, SPEED_MOTOR_PIN, 0x00);
	pulse = PULSE_ON;
	timer2_stop();
	break;	
		
	default:
	break;
	}
}

/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/