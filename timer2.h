/*
 * timer2.h
 *
 * Created: 04-Mar-2018
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


#ifndef TIMER2_H_
#define TIMER2_H_

/*----------------------------------------------------------------
--------------------- File Inclusions ----------------------------
----------------------------------------------------------------*/
#include <stdint.h>




/*----------------------------------------------------------------
--------------------- Public Function Prototypes ----------------
----------------------------------------------------------------*/
extern void timer2_init(void);
extern void timer2_stop(void);
extern void timer2_start(void);
extern void timer2_load_ocr2(uint8_t value_to_load_ocr2);
#endif /* TIMER2_H_ */