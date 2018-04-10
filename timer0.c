/*
 * timer.c
 *
 *	Created: 02-Mar-2018 
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
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "timer0.h"


/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/

typedef enum{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASE_CORRECT_PWM_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE
}timer_mode_t;


typedef enum{
	TIMER0_NO_CLK=0,						//No clock source (Timer/Counter stopped).
	TIMER0_NO_PRESCALAR,					//clk / (No prescaling)
	TIMER0_PRESCALAR8,						//clk / 8
	TIMER0_PRESCALAR64,						//clk / 64
	TIMER0_PRESCALAR256,					//clk / 256
	TIMER0_PRESCALAR1024,					//clk / 1024
	TIMER0_EXTERNAL_CLOCK_FALLING_EDGE,		//
	TIMER0_EXTERNAL_CLOCK_RISING_EDGE		//
}timer_prescalar_t;


/*----------------------------------------------------------------
--------------------- Private Function Declarations --------------
----------------------------------------------------------------*/
static void timer0_mode_set(timer_mode_t timer_mode);

static void timer0_prescalar_set(timer_prescalar_t timer_prescalar);

static void timer0_interrupt_enable(timer_mode_t timer_mode);

static void timer0_interrupt_disable(void);

static void timer0_TCNT0_load(uint8_t value_to_load);

static void timer0_OCR0_load( uint8_t value_to_load);

static void timer0_create_delay_us(uint8_t value_to_load_ocr0, timer_prescalar_t timer_prescalar);

static void timer0_pwm_duty_cycle_set(uint8_t duty_cycle_percentage);


/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/

void timer0_init(void)
{
	timer0_TCNT0_load(0);
	timer0_OCR0_load(156);						//loaded with a value to create 10ms TICK at 16mhz system clock frequency
	timer0_mode_set(TIMER0_CTC_MODE);
	timer0_interrupt_enable(TIMER0_CTC_MODE);
}
void timer0_start(void)
{
	timer0_prescalar_set(TIMER0_PRESCALAR1024);
}

	

/*----------------------------------------------------------------
--------------------- Private Function Definitions ---------------
----------------------------------------------------------------*/
	static void timer0_mode_set(timer_mode_t timer_mode)
	{
		switch (timer_mode)
		{
			case TIMER0_NORMAL_MODE:
			TCCR0 &= ~((1<<WGM01)|(1<<WGM00));
			break;
		
			case TIMER0_CTC_MODE:
			TCCR0 |= (1<<WGM01);
			TCCR0 &= ~(1<<WGM00);
			break;
		
			case TIMER0_FAST_PWM_MODE:
			TCCR0 |= ((1<<WGM01)|(1<<WGM00));
			TCCR0 |= (1<<COM01);				//Non-inverted fast PWM mode.
			TCCR0 &= ~(1<<COM00);
			DDRB  |= (1<<3);					//setting OC0 as output to output the PWM signal
			break;

			default:
			break;
		}
	
	}



	static void timer0_prescalar_set(timer_prescalar_t timer_prescalar)
	{
		
		switch (timer_prescalar)
		{
			case TIMER0_NO_CLK:
			TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
			break;
		
			case TIMER0_NO_PRESCALAR:
			TCCR0 &= ~((1<<CS02)|(1<<CS01));
			TCCR0 |= (1<<CS00);
			break;
		
			case TIMER0_PRESCALAR8:
			TCCR0 &= ~((1<<CS02)|(1<<CS00));
			TCCR0 |= (1<<CS01);
			break;
		
			case TIMER0_PRESCALAR64:
			TCCR0 |=  ((1<<CS01)|(1<<CS00));
			TCCR0 &= ~(1<<CS02);
			break;
		
			case TIMER0_PRESCALAR256:
			TCCR0 &= ~((1<<CS01)|(1<<CS00));
			TCCR0 |= (1<<CS02);
			break;
		
			case TIMER0_PRESCALAR1024:
			TCCR0 |=  ((1<<CS02)|(1<<CS00));
			TCCR0 &= ~(1<<CS01);
			break;
		
			case TIMER0_EXTERNAL_CLOCK_FALLING_EDGE:
			TCCR0 |=  ((1<<CS02)|(1<<CS01));
			TCCR0 &= ~(1<<CS00);
			break;
		
			case TIMER0_EXTERNAL_CLOCK_RISING_EDGE:
			TCCR0 |= ((1<<CS02)|(1<<CS01)|(1<<CS00));
			break;
		
			default:
			break;
		}
	
	}

	
	
	static void timer0_interrupt_enable(timer_mode_t timer_mode)
	{
		switch(timer_mode)
		{
		case TIMER0_NORMAL_MODE:
		TIMSK |= (1<<TOIE0);
		sei();
		break;
	
		case TIMER0_CTC_MODE:
		TIMSK |= (1<<OCIE0);
		sei();
		break;
	
		default:
		break;
		}
	}

	static void timer0_interrupt_disable(void)
	{
			TIMSK &= ~((1<<TOIE0)|(1<<OCIE0));
	}


	static void timer0_TCNT0_load(uint8_t value_to_load)
	{
		TCNT0  = value_to_load;
	}

	static void timer0_OCR0_load( uint8_t value_to_load)
	{
		OCR0 = value_to_load;
	}

	static void timer0_create_delay_us(uint8_t value_to_load_ocr0, timer_prescalar_t timer_prescalar)
	{
			
			TIMSK &= ~((1<<TOIE0)|(1<<OCIE0));		//disable the timer interrupts.
			TCNT0 = 0;								//to make sure you are starting clean.
			OCR0 = value_to_load_ocr0;				//loading ocr0 register with the desired value.
			switch (timer_prescalar)				//setting the timer clock prescalar.
			{
				case TIMER0_NO_PRESCALAR:
				TCCR0 &= ~((1<<CS02)|(1<<CS01));
				TCCR0 |= (1<<CS00);
				break;
				
				case TIMER0_PRESCALAR8:
				TCCR0 &= ~((1<<CS02)|(1<<CS00));
				TCCR0 |= (1<<CS01);
				break;
				
				case TIMER0_PRESCALAR64:
				TCCR0 |=  ((1<<CS01)|(1<<CS00));
				TCCR0 &= ~(1<<CS02);
				break;
				
				case TIMER0_PRESCALAR256:
				TCCR0 &= ~((1<<CS01)|(1<<CS00));
				TCCR0 |= (1<<CS02);
				break;
				
				case TIMER0_PRESCALAR1024:
				TCCR0 |=  ((1<<CS02)|(1<<CS00));
				TCCR0 &= ~(1<<CS01);
				break;
				
				default:
				break;
			}
			while((TIFR & (1<<OCF0)) == 0);										 //check compare match flag. 
			TCCR0 = 0x00;														 //stop timer. 
			TIFR |= (1<<OCF0);													 //clear flag.
		
	}

 static void timer0_pwm_duty_cycle_set(uint8_t duty_cycle_percentage)
 {
	 OCR0 =( ( (duty_cycle_percentage * 256) / 100) - 1 ); //equation of the inverted mode
 }

/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/


