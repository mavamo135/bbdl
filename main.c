/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/** 
 *  @file       usrleds.c 
 *	@brief      User LEDs driver interface
 *	@author     Maximiliano Valencia
 *	@date       4/10/2018
 */
 
/* Drivers Header File */
#include "drivers/driver.h"
/* User LEDs Driver Header File */
#include "drivers/usrleds.h"
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
    
	uart_properties *uart = malloc(sizeof(uart_properties));
	uart->uart_id = uart1;
    uart->baudrate = B9600;
    if(uart_open(uart) < 0) {
        perror("UART: Error opening UART\n");
    }
    sprintf(buf, "Hello!\n");
    
    while(keepRunning) {
        usrleds_write(LED1, 1);
        sleep(1);
        usrleds_write(LED1, 0);
        sleep(1);
        if (uart_write(uart, buf, strlen(buf) + 1) < 0) {
			perror("Could not send data to UART peripheral\n");
			return -1;
        }
    }
    uart_close(uart);
    printf("[INFO] Process finished!\n");
    return 0;
}

