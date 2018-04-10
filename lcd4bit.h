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
--------------------- Header Guard -------------------------------
----------------------------------------------------------------*/
#ifndef LCD_H_
#define LCD_H_

/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/
#include <stdint.h>




/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void lcd_init(void);
extern void lcd_update(void);
extern void lcd_turn_off(void);
extern void lcd_turn_on(void);
#endif /* LCD_H_ */


/*----------------------------------------------------------------
--------------------- End of File --------------------------------
----------------------------------------------------------------*/