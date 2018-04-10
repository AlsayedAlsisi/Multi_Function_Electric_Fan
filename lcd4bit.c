/*
 * lcd.h
 *
 * Created: 20-Mar-18 7:32:26 PM
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
#define F_CPU  16000000UL
#include "lcd4bit.h"
#include "gpio.h"
#include "timer0.h"
#include "speedControl.h"
#include "swingControl.h"
#include "sw.h"
#include "buzzer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h> 

/*----------------------------------------------------------------
--------------------- Private Constants --------------------------
----------------------------------------------------------------*/
#define LCD_PORT		PORT_C  //lcd port

#define LCD_DB4_PIN		PIN_4
#define LCD_DB5_PIN		PIN_5
#define LCD_DB6_PIN		PIN_6
#define LCD_DB7_PIN		PIN_7

#define LCD_RS_PIN		PIN_0
#define LCD_RW_PIN		PIN_1
#define LCD_EN_PIN		PIN_2

#define LCD_POWER_EN_PORT		PORT_A  
#define LCD_POWER_EN_PIN		PIN_7

/*----------------------------------------------------------------
--------------------- Private Data Types -------------------------
----------------------------------------------------------------*/
typedef enum{
	LCD_SPEED_SETTING_MODE = 0,
	LCD_SWING_SETTING_MODE,
	LCD_OFF_MODE 
	}lcd_mode_t;

/*----------------------------------------------------------------
--------------------- Private Variable Definitions ---------------
----------------------------------------------------------------*/
static lcd_mode_t lcd_current_mode =  LCD_SPEED_SETTING_MODE;

/*----------------------------------------------------------------
--------------------- Private Functions Prototypes ---------------
----------------------------------------------------------------*/
static void lcd_command_send(char cmnd);

static void lcd_data_send(char data);

static void lcd_gotoxy(uint8_t x, uint8_t y);

static void lcd_string_display(char* str);


/*----------------------------------------------------------------
--------------------- Public Function Definitions ----------------
----------------------------------------------------------------*/

void lcd_init(void)
{
	gpio_init_port_pin(LCD_PORT, (LCD_DB7_PIN|LCD_DB6_PIN|LCD_DB5_PIN|LCD_DB4_PIN) ,OUTPUT, 0x00);
	gpio_init_port_pin(LCD_PORT, (LCD_EN_PIN|LCD_RW_PIN|LCD_RS_PIN)			       ,OUTPUT, 0x00);
	gpio_init_port_pin(LCD_POWER_EN_PORT, LCD_POWER_EN_PIN, OUTPUT, 0xff); 
	
	gpio_write_port_pin(LCD_PORT,(LCD_RS_PIN|LCD_RW_PIN), 0x00);
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0x00);
	_delay_us(2000);
	lcd_command_send(0x33); //for 4-bit mode
	_delay_us(100);
	lcd_command_send(0x32); //for 4-bit mode
	_delay_us(100);
	lcd_command_send(0x28); //for 4-bit mode
	_delay_us(100);
	lcd_command_send(0x0C); //display on, cursor off.
	_delay_us(100);
	lcd_command_send(0x01); //clear lcd
	_delay_us(2000);
	lcd_command_send(0x06); //No shift and auto increment right
	_delay_us(100);
	
}

 void lcd_update(void)
{
	static uint16_t lcd_swing_mode_time_counter=0;
	switch(lcd_current_mode)
	{
		case LCD_SPEED_SETTING_MODE:
		lcd_gotoxy(2,0);					//going to LCD line 1, column 3
		lcd_string_display("Motor Speed");	//Displaying "Motor Speed" on the 1st line of the LCD.
		lcd_gotoxy(0,1);					//going to LCD line 2, column 0
		lcd_string_display("Speed=");		//Displaying the current speed setting on the 2nd line of the LCD.
		//displaying current speed setting:
		switch (speed_current_state_get())
		{
			case SPEED_MIN:
			lcd_string_display("MIN       ");
			break;

			case SPEED_MID:
			lcd_string_display("MID       ");
			break;
			case SPEED_MAX:
			lcd_string_display("MAX       ");
			break;
			
			default:
			break;
		}
				
		if (display_sw_state_get() == FALLING_EDGE)
		{
			buzzer_start();
			lcd_current_mode = LCD_SWING_SETTING_MODE;
		}

		break;
		
		case LCD_SWING_SETTING_MODE:
		lcd_swing_mode_time_counter += TIMER_TICK;
		lcd_gotoxy(2,0);					//going to LCD line 1, column 3
		lcd_string_display("Swing Value");	//Displaying "Motor Speed" on the 1st line of the LCD.
		lcd_gotoxy(0,1);					//going to LCD line 2, column 0
		//displaying current swing setting:
		switch(swing_degree_current_state_get())
		{
			case SWING_DEGREE0:
			lcd_string_display("                ");
			break;
			
			case SWING_DEGREE45:
			lcd_string_display("       **       ");
			break;
			
			case SWING_DEGREE90:
			lcd_string_display("      ****      ");
			break;
			
			case SWING_DEGREE135:
			lcd_string_display("     ******     ");
			break;
			
			case SWING_DEGREE180:
			lcd_string_display("    ********    ");
			break;
			
			case SWING_DEGREE225:
			lcd_string_display("   **********   ");
			break;
			
			case SWING_DEGREE270:
			lcd_string_display("  ************  ");
			break;
			
			case SWING_DEGREE315:
			lcd_string_display(" ************** ");
			break;
			
			case SWING_DEGREE360:
			lcd_string_display("****************");
			break;
			
			default:
			break;
		}
		if (display_sw_state_get() == FALLING_EDGE ) 
		{
			lcd_swing_mode_time_counter = 0;
			buzzer_start();
			lcd_current_mode = LCD_SPEED_SETTING_MODE;
			
		}
		else if (lcd_swing_mode_time_counter == 20000) //if 20 seconds has passed, or the sw was pressed
		{
			lcd_swing_mode_time_counter = 0;
			lcd_current_mode = LCD_SPEED_SETTING_MODE;
		}
		break;
		
		case LCD_OFF_MODE:
		gpio_write_port_pin(LCD_POWER_EN_PORT, LCD_POWER_EN_PIN, 0x00); // LCD_POWER_EN_PIN = 0
		break;
		
		default:
		break;
	}
}
 void lcd_turn_off(void)
{
	lcd_current_mode = LCD_OFF_MODE;
}
 void lcd_turn_on(void)
{
	lcd_current_mode = LCD_SPEED_SETTING_MODE;
}
/*----------------------------------------------------------------
--------------------- Private Functions Definitions --------------
----------------------------------------------------------------*/
static void lcd_command_send(char cmnd)
{
	//Sending the first part of the data:
	gpio_write_port_pin(LCD_PORT, (LCD_DB7_PIN|LCD_DB6_PIN|LCD_DB5_PIN|LCD_DB4_PIN), cmnd);
	
	gpio_write_port_pin(LCD_PORT,(LCD_RS_PIN|LCD_RW_PIN), 0x00); // RS = RW = 0
	
	//High-to-Low pulse on Enable pin:
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0xff);
	_delay_us(100);
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0x00);
	
	_delay_us(200);
	
	//Sending the second part of the data:
	gpio_write_port_pin(LCD_PORT, (LCD_DB7_PIN|LCD_DB6_PIN|LCD_DB5_PIN|LCD_DB4_PIN), (cmnd<<4));
	
	//High-to-Low pulse on Enable pin:
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0xff);
	_delay_us(100);
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0x00);
}

static void lcd_data_send(char data)
{
	//Sending the first part of the data:
	gpio_write_port_pin(LCD_PORT, (LCD_DB7_PIN|LCD_DB6_PIN|LCD_DB5_PIN|LCD_DB4_PIN), data);
	
	gpio_write_port_pin(LCD_PORT, LCD_RS_PIN, 0xff);	//RS = 1
	gpio_write_port_pin(LCD_PORT, LCD_RW_PIN, 0x00);	//RW = 0
	
	//High-to-Low pulse on Enable pin:
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0xff);
	_delay_us(100);
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0x00);
	
	_delay_us(200);
	
	//Sending the second part of the data:
	gpio_write_port_pin(LCD_PORT, (LCD_DB7_PIN|LCD_DB6_PIN|LCD_DB5_PIN|LCD_DB4_PIN), (data<<4));
	
	//High-to-Low pulse on Enable pin:
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0xff);
	_delay_us(100);
	gpio_write_port_pin(LCD_PORT, LCD_EN_PIN, 0x00);
}

static void lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t first_char_address[]={0x80, 0xC0,0x90, 0xD0}; //This is for 16x4 LCD. For 20x4, put it on this way: {0x80, 0xC0,0x94, 0xD4}
	lcd_command_send(first_char_address[y]+(x));
	_delay_us(100);	
}



static void lcd_string_display(char* str)
{
	uint8_t i=0;
	while (str[i]!=0)
	{
		lcd_data_send(str[i]);
		i++;
	}
}