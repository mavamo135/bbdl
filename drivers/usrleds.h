/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of BeagleBone Black Drivers Library (BBDL).            *
 *                                                                          *
 *   BBBDL is free software: you can redistribute it and/or modify it       *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   BBDL is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
 
/*!
 *  @file       userleds.h
 *	@author 	Maximiliano Valencia
 *	@date		4/10/2018
 *  @brief      User LEDs driver interface
 *
 *  The User LEDs header file should be included in an application as follows:
 *  @code
 *  #include "drivers/userleds.h"
 *  @endcode
 *
 *  # Overview #
 *  The User LEDs module allows you to manage on-board User LEDs via simple
 *  and portable APIs.
 *
 *  # Usage #
 *  The following code example demonstrates how
 *  to configure and use a User LED 
 *
 *  @code
 *  #include <stdint.h>
 *  #include <stddef.h>
 *
 *  // User LEDs Header file
 *  #include <ti/drivers/GPIO.h>
 *
 *  main()
 *  {
 *      // Call GPIO driver init function
 *      USRLEDSinit();
 *
 *      // Turn on User LED 1
 *      USRLEDS_write(LED1, 1);
 *
 *  }
 *
 *  @endcode
 *
 *  ### Initializing the User LEDs Driver #
 *
 *  USRLEDS_init() must be called before any other User LEDs APIs.  This function
 *  configures all the available User LEDs.
 *
 *  ============================================================================
 */
 
#ifndef __USRLEDS_H_
#define __USRLEDS_H_

/*!
 *  @brief      USR LEDS file descriptor location 
 */
#define LED1 "/sys/class/leds/beaglebone:green:usr0"
#define LED2 "/sys/class/leds/beaglebone:green:usr1"
#define LED3 "/sys/class/leds/beaglebone:green:usr2"
#define LED4 "/sys/class/leds/beaglebone:green:usr3"

/*!
 *  @brief  Initializes the User LEDs module
 *
 *  All the available User LEDs are initialized.
 *
 */
void usrleds_init();

/*!
 *  @brief     Writes the value to a User LED
 *
 *  @param      led    Selected User LED
 *  @param      value   must be either 0 or 1
 */
void usrleds_write(char* led, int value);

/*!
 *  @brief      Makes the selected User LED flash
 *
 *  @param      led    Selected User LED
 */
void usrleds_flash(char* led);

#endif /* __USRLEDS_H_ */