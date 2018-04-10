/*
 * Multi-Function Fan.c
 *
 * Created: 01-Apr-18 11:21:50 PM
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
#include "adc.h"
#include "buzzer.h"
#include "lcd4bit.h"
#include "speedControl.h"
#include "sw.h"
#include "swingControl.h"
#include "timer2.h"
#include "timer0.h"
#include "timerControl.h"
#include "ssd.h"
#include "fanPowerControl.h"

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	adc_init();
	timer2_init();
	timer0_init();
	sw_init();
	speed_control_init();
	swing_control_init();
	buzzer_init();
	ssd_init();
	lcd_init();
	timer0_start();
	
    while (1) 
    {
		//Should go to sleep
    }
}


ISR(TIMER0_COMP_vect)
{

	sw_update();
	fan_power_update();
	swing_control_update();
	speed_control_update();
	timer_control_update();
	ssd_update();
	buzzer_update();
	lcd_update();
	
}
