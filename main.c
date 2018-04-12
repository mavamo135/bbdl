/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of BeagleBone Black Drivers Library (BBDL).            *
 *                                                                          *
 *   BBDL is free software: you can redistribute it and/or modify it       *
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

/** 
 *  @file       main.c 
 *	@brief      BBDL Examples
 *	@author     Maximiliano Valencia
 *	@date       4/10/2018
 */
 
/* Drivers Header File */
#include "drivers/driver.h"
/* User LEDs Driver Header File */
#include "drivers/usrleds.h"
/* GPIO Driver Header File */
#include "drivers/gpio.h"
/* UART Driver Header File */
#include "drivers/uart.h"

int keepRunning = 1;

void closeHandler(void) {
    keepRunning = 0;
    printf("[INFO] CTRL-C catched!\n");
}

int main(void) {
    char buf[30];
    
    drivers_init(&closeHandler);
    
    usrleds_init();
    
    gpio_properties *gpio = malloc(sizeof(gpio_properties));
    gpio->nr = 60;
    gpio->direction = OUTPUT_PIN;
    if(gpio_open(gpio) < 0) {
        printf("GPIO: Error opening GPIO %d\n", gpio->nr);
    }
    gpio_write(gpio, 1);
    
	uart_properties *uart = malloc(sizeof(uart_properties));
	uart->uart_id = uart1;
    uart->baudrate = B9600;
    if(uart_open(uart) < 0) {
        printf("UART: Error opening UART %d\n", uart->uart_id);
    }
    sprintf(buf, "Hello!\n");
    
    while(keepRunning) {
        usrleds_write(LED1, 1);
        sleep(1);
        usrleds_write(LED1, 0);
        sleep(1);
        if (uart_write(uart, buf, strlen(buf) + 1) < 0) {
			printf("Could not send data to UART peripheral\n");
			return -1;
        }
    }
    gpio_close(gpio);
    free(gpio);
    uart_close(uart);
    printf("[INFO] Process finished!\n");
    return 0;
}

