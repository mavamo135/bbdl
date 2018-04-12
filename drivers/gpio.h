/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of BeagleBone Black Drivers Library (BBDL).            *
 *                                                                          *
 *   BBDL is free software: you can redistribute it and/or modify it        *
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
 *   License along with BBDL.  If not, see <http://www.gnu.org/licenses/>.  *
 ****************************************************************************/
 
/*!
 *  @file       gpio.h
 *	@author 	Maximiliano Valencia
 *	@date		4/11/2018
 *  @brief      GPIO driver interface
 *
 *  The GPIO header file should be included in an application as follows:
 *  @code
 *  #include "drivers/gpio.h"
 *  @endcode
 *
 *  # Overview #
 *  The GPIO module allows you to manage General Purpose I/O pins via simple
 *  and portable APIs.
 *
 *  # Usage #
 *  The following code example demonstrates how to configure and use a GPIO.
 *
 *  @code
 *  #include <stdint.h>
 *  #include <stddef.h>
 *
 *  // GPIO Header file
 *  #include "drivers/gpio.h>
 *
 *  main()
 *  {
 *      gpio_properties *gpio = malloc(sizeof(gpio_properties));
 *	    gpio->nr = LEDGPIO;
 *	    gpio->direction = OUTPUT_PIN;
 *
 *	    int isOpen = gpio_open(gpio);
 *
 *	    if (isOpen == 0) {
 *			gpio_set_value(gpio, 1);
 *		}
 *		
 * 		gpio_close(gpio);
 *      free(gpio);
 *  }
 *
 *  @endcode
 *
 *  ### Initializing the GPIO Driver #
 *
 *  gpio_init() must be called before any other GPIO APIs.  This function
 *  configures a GPIO peripheral.
 *
 *  ============================================================================
 */
 
#ifndef __GPIO_H_
#define __GPIO_H_

/*!
 *  @brief      GPIO file location 
 */
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

/*!
 *  @brief      PIN direction
 */
typedef enum {
	INPUT_PIN=0,
	OUTPUT_PIN=1
} PIN_DIRECTION;

/*!
 *  @brief      GPIO properties structure type definition
 */
typedef struct {
	int nr;
	PIN_DIRECTION direction;
} gpio_properties;

/*!
 *  @brief  Function to initialize a given GPIO peripheral
 *
 *  Function to initialize a given GPIO peripheral specified by the
 *  gpio_properties structure.
 *
 *  @param  gpio    A gpio_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t gpio_open(gpio_properties *gpio);

/*!
 *  @brief  Writes the value to a GPIO
 *
 *  @pre    gpio_open()
 *
 *  @param  gpio    A gpio_properties structure
 *  @param  value   must be either 0 or 1
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t gpio_write(gpio_properties *gpio, int value);

/*!
 *  @brief  Reads the value of a GPIO
 *
 *  @pre    gpio_open()
 *
 *  @param  gpio    A gpio_properties structure
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t gpio_read(gpio_properties *gpio);

/*!
 *  @brief  Set a GPIO to provide an event on a edge
 *
 *  @pre    gpio_open()
 *
 *  @param  gpio    A gpio_properties structure
 *  @param  edge    Edge that produces the event
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t gpio_edge(gpio_properties *gpio, char *edge);

/*!
 *  @brief  Function to close a given GPIO peripheral
 *
 *  @pre    gpio_open()
 *
 *  @param  gpio    A gpio_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t gpio_close(gpio_properties *gpio);

#endif /* GPIO_H_ */