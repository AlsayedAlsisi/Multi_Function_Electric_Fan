/*
 * gpio.h
 *
 * Created: 28-Feb-18 1:54:23 PM
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

/*-------------------------------------------------------------------------------------------------
------------------------------------ Header Guard -------------------------------------------------
-------------------------------------------------------------------------------------------------*/
#ifndef GPIO_H_
#define GPIO_H_

/*-------------------------------------------------------------------------------------------------
------------------------------------ File Inclusions ----------------------------------------------
-------------------------------------------------------------------------------------------------*/
#include <stdint.h>

/*-------------------------------------------------------------------------------------------------
------------------------------------ Public Constants --------------------------------------------
-------------------------------------------------------------------------------------------------*/
#define 	PIN_0  0b00000001
#define 	PIN_1  0b00000010
#define 	PIN_2  0b00000100
#define 	PIN_3  0b00001000
#define 	PIN_4  0b00010000
#define 	PIN_5  0b00100000
#define 	PIN_6  0b01000000
#define 	PIN_7  0b10000000
	


/*-------------------------------------------------------------------------------------------------
------------------------------------ Public Data Types --------------------------------------------
-------------------------------------------------------------------------------------------------*/
typedef enum port_number{
  PORT_A=0,
  PORT_B,
  PORT_C,
  PORT_D
} port_number_t;


typedef enum direction{
  INPUT=0,
  OUTPUT
} direction_t;





/*-------------------------------------------------------------------------------------------------
------------------------------------ Public Function Prototypes -----------------------------------
-------------------------------------------------------------------------------------------------*/


/**************************************************************************************************
The  following  function is used to initialize an entire port as input or output.
In case of setting the port as output, the initial_state sets the initial state of the port pins to  
HIGH  or LOW. And in case of setting  the  port as  input, initial state can be used to set pull-up 
resistors. Examples: 
- Setting portb as output with initial value of all pins as HIGH:s
      gpio_init_port(PORT_B, OUTPUT, 0xff);
- Setting portd as input with all pull-up resistors enabled:
      gpio_init_port(PORT_D,  INPUT, 0xff); 
**************************************************************************************************/
void gpio_init_port(port_number_t port_number, direction_t port_direction, uint8_t port_initial_state);//tested


/**************************************************************************************************
The following function is used to output certain value on all the pins of the selected port in case
the port is set as output. Or to enable the pull-up resistors on certain pins of the  selected port 
in case the port is set as input. Examples:
  gpio_set_port(PORT_A, 0xf0); //output +5v on PIN_7, PIN_6, PIN_5, and PIN_4 and 0v on other
						       //pins. PORT_A is set as output
  gpio_set_port(PORT_A, 0xf0); //enable the pull-up resistors on PIN_7, PIN_6, PIN_5, and PIN_4 
							   //pins. PORT_A is set as input

**************************************************************************************************/
void gpio_write_port(port_number_t port_number, uint8_t port_state);



/**************************************************************************************************
The following function is used to read the value on the pins of a port that is configured as input.
**************************************************************************************************/
uint8_t gpio_read_port(port_number_t port_number);



/**************************************************************************************************
The following function is used to initialize a single pin or a group of pins as input or output. 
In case of setting the pin/pins as output, the initial_state sets the initial value of the pin/pins
as HIGH or LOW.  And in  case  of  setting the pin as input, initial value can be used to  enable 
pull-up resistor. Examples:
- setting  pin0  of  portb as output with initial value HIGH:
	gpio_init_port_pin(PORT_B, PIN_0, OUTPUT, HIGH); 
- setting pin0 of portd as input with pull-up resistor enabled:
	gpio_init_port(PORT_D,  PIN_0, INPUT, HIGH); 
**************************************************************************************************/
void gpio_init_port_pin(port_number_t port_number, uint8_t pin_number, direction_t pin_direction, uint8_t pin_initial_state);





/**************************************************************************************************
The following function is used to write +5v or 0v to a single pin or a group of pins of a certain port
in case the pin/pins are set as output. Or to enable the pull-up resistors on certain pin/pins of the  
selected port in case the pin/pins is set as input.
Example:
	gpio_write_port_pin(PORT_A, PIN_5, 0b 0010 0000);
	gpio_write_port_pin(PORT_A, (PIN_5|PIN_0), 0b 0010 0001);
**************************************************************************************************/
void gpio_write_port_pin(port_number_t port_number, uint8_t pin_number, uint8_t pin_state);




/**************************************************************************************************
The following function is used to read the value of a single pin or a group of pins of a certain 
port that are configured as input. Examples:
	gpio_read_port_pin(PORT_A, PIN_5);
	gpio_read_port_pin(PORT_A, (PIN_5|PIN_0));
**************************************************************************************************/
uint8_t gpio_read_port_pin(port_number_t port_number, uint8_t pin_number);


#endif /* GPIO_H_ */

/*-------------------------------------------------------------------------------------------------
------------------------------------ End of File --------------------------------------------------
-------------------------------------------------------------------------------------------------*/
