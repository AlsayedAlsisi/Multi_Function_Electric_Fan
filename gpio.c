/*
 * gpio.c
 *
 * Created: 28-Feb-18 7:58:27 PM
 * Copyright: Alsayed Alsisi
 * Author: Alsayed Alsisi
 * License:
 You have the freedom to use the code in educational or commercial purposes under the following conditions:
 - You don't remove my name under any circumstances.
 - You use the code as is. And if you need to edit it
 */ 
/*-------------------------------------------------------------------------------------------------
------------------------------------ File Inclusions ----------------------------------------------
-------------------------------------------------------------------------------------------------*/
#include "gpio.h"
#include "stdint.h"
#include <avr/io.h>



/*-------------------------------------------------------------------------------------------------
------------------------------------ Public Function Definitions ----------------------------------
-------------------------------------------------------------------------------------------------*/

void gpio_init_port(port_number_t port_number, direction_t port_direction, uint8_t port_initial_state)  //tested
{
  switch (port_direction)
  {
    case INPUT:
      switch (port_number)
      {
        
        case PORT_A:
        DDRA=0x00;
        PORTA =  port_initial_state;
        break;
        
        case PORT_B:
        DDRB=0x00;
        PORTB =  port_initial_state;
        break;
        
        case PORT_C:
        DDRC=0x00;
        PORTC =  port_initial_state;
        break;
        
        case PORT_D:
        DDRD=0x00;
        PORTD =  port_initial_state;
        break;
        
        default:
        break;
        
      }
    break;
    case OUTPUT:
      switch (port_number)
      {
        case PORT_A:
        DDRA=0xff;
        PORTA =  port_initial_state;
        break;
        
        case PORT_B:
        DDRB=0xff;
        PORTB =  port_initial_state;
        break;
        
        case PORT_C:
        DDRC=0xff;
        PORTC =  port_initial_state;
        break;
        
        case PORT_D:
        DDRD=0xff;
        PORTD =  port_initial_state;
        break;
        
        default:
        break;
      }
    break;
	
	default:
	break;
  }
}

void gpio_write_port(port_number_t port_number, uint8_t port_state) //tested
{
	switch (port_number)
	{
		
		case PORT_A:
		PORTA = port_state;
		break;
		
		case PORT_B:
		PORTB =  port_state;
		break;
		
		case PORT_C:
		PORTC =  port_state;
		break;
		
		case PORT_D:
		PORTD =  port_state;
		break;
		
		default:
		break;
		
	}
	
}

uint8_t gpio_read_port(port_number_t port_number) //tested
{
	uint8_t port_state=0;
	switch (port_number)
	{
		case PORT_A:
		port_state = PINA ;
		break;
		
		case PORT_B:
		port_state = PINB ;
		break;
		
		case PORT_C:
		port_state = PINC ;
		break;
		
		case PORT_D:
		port_state = PIND ;
		break;
		
		default:
		break;
	}
	
	return port_state;
}


void gpio_init_port_pin(port_number_t port_number, uint8_t pin_number, direction_t pin_direction, uint8_t pin_initial_state) //tested
{
  switch (pin_direction)
  {
    case INPUT:
      switch (port_number)
      {
        case PORT_A:
        DDRA &= ~(pin_number);
		PORTA = ((PORTA & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_B:
        DDRB &= ~(pin_number);
        PORTB = ((PORTB & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_C:
        DDRC &= ~(pin_number);
        PORTC = ((PORTC & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_D:
        DDRD &= ~(pin_number);
        PORTD = ((PORTD & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        default:
        break;
      }
	 break;
    
    case OUTPUT:
      switch (port_number)
      {
        case PORT_A:
        DDRA |= (pin_number);
        PORTA = ((PORTA & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_B:
        DDRB |= (pin_number);
        PORTB = ((PORTB & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_C:
        DDRC |= (pin_number);
        PORTC = ((PORTC & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        case PORT_D:
        DDRD |= (pin_number);
        PORTD = ((PORTD & ~(pin_number)) | (pin_number & pin_initial_state));
        break;
        
        default:
        break;
      }
	break;
	
	default:
	break;
  }
  
}


void gpio_write_port_pin(port_number_t port_number, uint8_t pin_number, uint8_t pin_state) //tested
{
	  switch (port_number)
	  {
		  case PORT_A:
		  PORTA = ((PORTA & ~(pin_number)) | (pin_number & pin_state));
		  break;
		  
		  case PORT_B:
		  PORTB = ((PORTB & ~(pin_number)) | (pin_number & pin_state));
		  break;
		  
		  case PORT_C:
		  PORTC = ((PORTC & ~(pin_number)) | (pin_number & pin_state));
		  break;
		  
		  case PORT_D:
		  PORTD = ((PORTD & ~(pin_number)) | (pin_number & pin_state));
		  break;
		  
		  default:
		  break;
	  }
}



uint8_t gpio_read_port_pin(port_number_t port_number, uint8_t pin_number) //tested
{
  uint8_t pin_state=0;

  switch (port_number)
  {
    case PORT_A:
    pin_state = (PINA & (pin_number)) ;
    
    break;
    
    case PORT_B:
     pin_state = (PINB & (pin_number)) ;
    break;
    
    case PORT_C:
     pin_state = (PINC & (pin_number)) ;
    break;
    
    case PORT_D:
     pin_state = (PIND & (pin_number)) ;
    break;
    
    default:
    break;
  }
  
  return pin_state;
}

/*-------------------------------------------------------------------------------------------------
------------------------------------ End of File --------------------------------------------------
-------------------------------------------------------------------------------------------------*/
