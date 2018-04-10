/*
 * ssd.c
 *
 * Created: 06-Mar-18 7:20:14 PM
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
#include "timerControl.h"
#include "timer0.h"

/*----------------------------------------------------------------
--------------------- Private Constants ---------------------------
----------------------------------------------------------------*/
#define SSD_MINUTS_ONES_DATA_PORT         PORT_D
#define SSD_MINUTS_ONES_EN_PORT           PORT_C
#define SSD_MINUTS_ONES_EN_PIN			  PIN_3

#define SSD_MINUTS_TENS_DATA_PORT         PORT_D
#define SSD_MINUTS_TENS_EN_PORT           PORT_B
#define SSD_MINUTS_TENS_EN_PIN			  PIN_7

#define SSD_HOURS_ONES_DATA_PORT          PORT_D
#define SSD_HOURS_ONES_EN_PORT            PORT_B
#define SSD_HOURS_ONES_EN_PIN			  PIN_6

#define SSD_HOURS_TENS_DATA_PORT          PORT_D
#define SSD_HOURS_TENS_EN_PORT            PORT_B
#define SSD_HOURS_TENS_EN_PIN			  PIN_5



/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum{
	SSD_STARTING,
	SSD_WORKING,
	SSD_STOPPED
} ssd_state_t;

typedef enum{
	SSD_STARTING_H,
	SSD_STARTING_I
} ssd_starting_state_t;

typedef enum{
	SSD_WORKING_MINUTS_ONES,
	SSD_WORKING_MINUTS_TENS,
	SSD_WORKING_HOURS_ONES,
	SSD_WORKING_HOURS_TENS
	}ssd_working_state_t;
	
/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
	static volatile uint8_t ssd_var=0;
	static unsigned char s_segment_display[]={0b00111111, 0b00000110,0b01011011, 0b01001111,0b01100110, 0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
	static ssd_state_t ssd_state = SSD_STARTING;
	static uint8_t minutes_var = 0;
	static uint8_t hours_var = 0;

/*----------------------------------------------------------------
--------------------- Private Function Declarations --------------
----------------------------------------------------------------*/
static void ssd_starting_multiplex(void);
static void ssd_working_multiplex(void);
	
/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/
void ssd_init(void)
{
	gpio_init_port(SSD_MINUTS_ONES_DATA_PORT, OUTPUT, 0x00);
	gpio_init_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, OUTPUT, 0x01);
	gpio_init_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, OUTPUT, 0x00);
	gpio_init_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  OUTPUT, 0x00);	
	gpio_init_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  OUTPUT, 0x00);

}
void ssd_update(void)
{
	static uint16_t ssd_starting_state_time_cnt = 0;

	if (timer_control_minutes_counter_value_get() == 0)
	{
		minutes_var = 0;
	}
	
	else 
	minutes_var = 60  - timer_control_minutes_counter_value_get();
	
	switch(ssd_state)
	{
		case SSD_STARTING:
		ssd_starting_state_time_cnt +=TIMER_TICK;
		ssd_starting_multiplex();
		if (ssd_starting_state_time_cnt == 10000)
		{
			ssd_starting_state_time_cnt = 0;
			ssd_state = SSD_WORKING;
		}
		break;
		
		case SSD_WORKING:
		ssd_working_multiplex();
		break;
		
		case SSD_STOPPED:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  0x00);
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		break;
		
		default:
		break;
		
	}
	
}

 void ssd_minutes_var_set(uint8_t arg)
 {
	 minutes_var = arg;
 }
 
 void ssd_hours_var_set(uint8_t arg)
 {
	 hours_var = arg;
 }
 
 void ssd_hours_var_decrement(void)
 {
	  hours_var--;
 }
 
 void ssd_turn_off(void)
{
	ssd_state = SSD_STOPPED;
}

 void ssd_turn_on(void)
{
	ssd_state = SSD_STARTING;
}

/*----------------------------------------------------------------
--------------------- Private Function Definitions ----------------
----------------------------------------------------------------*/
static void ssd_starting_multiplex(void)
{
	static ssd_starting_state_t ssd_starting_state = SSD_STARTING_H;
	switch(ssd_starting_state)
	{
		case SSD_STARTING_H:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, SSD_MINUTS_TENS_EN_PIN); 
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  0x00);
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		gpio_write_port(SSD_MINUTS_TENS_DATA_PORT, 0b00110000); //code to display 'H'
		ssd_starting_state = SSD_STARTING_I;
		break;
		
		case SSD_STARTING_I:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  SSD_HOURS_ONES_EN_PIN); 
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		gpio_write_port(SSD_HOURS_ONES_DATA_PORT, 0b01110110); //code to display 'I'
		ssd_starting_state = SSD_STARTING_H;
		break;
		
		default:
		break;
	}
}

static void ssd_working_multiplex(void)
{
	static ssd_working_state_t ssd_working_state= SSD_WORKING_MINUTS_ONES;
	switch(ssd_working_state)
	{
		case SSD_WORKING_MINUTS_ONES:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, SSD_MINUTS_ONES_EN_PIN); //SSD_MINUTS_ONES_EN_PIN translates to 0b00000001
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  0x00);
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		gpio_write_port(SSD_MINUTS_ONES_DATA_PORT, s_segment_display[(minutes_var%10)]);
		ssd_working_state = SSD_WORKING_MINUTS_TENS;
		break;
		
		case SSD_WORKING_MINUTS_TENS:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, SSD_MINUTS_TENS_EN_PIN); // SSD_MINUTS_TENS_EN_PIN translates to 0b00000010
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  0x00);
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		gpio_write_port(SSD_MINUTS_TENS_DATA_PORT, s_segment_display[(minutes_var/10)]);
		ssd_working_state = SSD_WORKING_HOURS_ONES;
		break;

		case SSD_WORKING_HOURS_ONES:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  SSD_HOURS_ONES_EN_PIN); //SSD_HOURS_ONES_EN_PIN translates to 0b00000100
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  0x00);
		gpio_write_port(SSD_HOURS_ONES_DATA_PORT, s_segment_display[(hours_var%10)]);
		ssd_working_state = SSD_WORKING_HOURS_TENS;
		break;

		case SSD_WORKING_HOURS_TENS:
		gpio_write_port_pin(SSD_MINUTS_ONES_EN_PORT, SSD_MINUTS_ONES_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_MINUTS_TENS_EN_PORT, SSD_MINUTS_TENS_EN_PIN, 0x00);
		gpio_write_port_pin(SSD_HOURS_ONES_EN_PORT,  SSD_HOURS_ONES_EN_PIN,  0x00);
		gpio_write_port_pin(SSD_HOURS_TENS_EN_PORT,  SSD_HOURS_TENS_EN_PIN,  SSD_HOURS_TENS_EN_PIN); //SSD_HOURS_TENS_EN_PIN translates to 0b00001000
		gpio_write_port(SSD_HOURS_TENS_DATA_PORT, s_segment_display[(hours_var/10)]);
		ssd_working_state = SSD_WORKING_MINUTS_ONES;
		break;
		
		default:
		break;
	}
}
/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/